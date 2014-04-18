#include <vector>
#include <clocale>
#include <memory>
#include <stdexcept>
#include "edgeextractor.h"
#include "normalsfinder.h"
#include "mesh.h"
#include "interface.h"
#include "flowrunner.h"
#include "plydatareader.h"
#include "flowfactory.h"

#ifndef NDEBUG
#include <fenv.h>
#endif

int main ( int argc, char *argv[] )
{
#ifndef NDEBUG
    fetestexcept ( FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW );
#endif

    setlocale ( LC_NUMERIC, "en_US" );
    
    if ( argc < 4 )
      throw std::runtime_error ( "Run with: <mesh.ply> <MEAN | POWER_MEAN> [int | null]" );
    
    Mesh mesh;
    PLYDataReader *reader = new PLYDataReader;
    reader->set ( &mesh );
    reader->read ( argv[1] );
    mesh.verify();

    delete reader;

    NormalsFinder * normalsFinder = new NormalsFinder;
    normalsFinder->set(&mesh);
    normalsFinder->execute();

    delete normalsFinder;

    EdgeExtractor * extractor = new EdgeExtractor;
    extractor->init ( &mesh );

    for ( unsigned int i = 0; i < mesh.vertex_count(); i++ )
    {
        extractor->extract(i);
        mesh.set_star_of(i, extractor->get() );
    }

    delete extractor;

    std::shared_ptr < FlowFilter > flowFilter = FlowFactory::get_flow ( argv[2], argv[3] );
    flowFilter->input ( &mesh );

    FlowRunner flowRunner ( flowFilter );

    Interface interface;
    flowRunner.register_listener(&interface);
    interface.register_listener(&flowRunner);
    interface.init( mesh );

    return interface.exec();
}
