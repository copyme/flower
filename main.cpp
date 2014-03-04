#include <vector>
#include <clocale>
#include "edgeextractor.h"
#include "normalsfinder.h"
#include "mesh.h"
#include "interface.h"
#include "flowrunner.h"
#include "plydatareader.h"

#ifndef NDEBUG
#include <fenv.h>
#endif

int main ( int argc, char *argv[] )
{
#ifndef NDEBUG
    fetestexcept ( FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW );
#endif

    setlocale ( LC_NUMERIC, "en_US" );

    Mesh mesh;
    PLYDataReader reader;
    reader.set ( &mesh );
    reader.read ( argv[1] );
    mesh.verify();

    NormalsFinder normalsFinder;
    normalsFinder.set(&mesh);
    normalsFinder.execute();

    std::cout << "Normals " << mesh.normal_count() << " faces " << mesh.face_count() << " vertices " << mesh.vertex_count() << std::endl;

    MeanFlowFilter meanFlowFilter;
    meanFlowFilter.input ( &mesh );

    FlowRunner flowRunner ( meanFlowFilter );

    Interface interface;
    flowRunner.register_listener(&interface);
    interface.register_listener(&flowRunner);
    interface.init( mesh );

    return interface.exec();
}