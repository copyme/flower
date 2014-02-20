#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include "plydatareader.h"
#include "edgeextractor.h"
#include "plydatawriter.h"
#include "meanflowfilter.h"
#include "normalsfinder.h"

int main ( int argc, char *argv[] )
{
    if ( argc < 3 )
    {
        std::cerr << "Please define input and output: PLY files.\n";
        exit ( EXIT_FAILURE );
    }
    Mesh mesh, mesh_out;
    PLYDataReader reader;
    reader.set ( &mesh );
    reader.read ( argv[1] );
    mesh.verify();
    
    NormalsFinder normalsFinder;
    normalsFinder.set(&mesh);
    normalsFinder.execute();
    
    EdgeExtractor ex;
    ex.init(&mesh);
    ex.extract(0);
    
    mesh_out.set_model( mesh.get_model() );
    
    //copy faces to output
    for ( unsigned int i = 0; i < mesh.face_count(); i++ )
    {
        Face face = mesh.get_face(i);
        for (unsigned int j = 0; j < face.model(); j++ )
            mesh_out.add_face_vertex(face[j]);
    }
    
    MeanFlowFilter meanFlowFilter;
    double step = .2;
    meanFlowFilter.set_time ( step );
    meanFlowFilter.input ( &mesh );
    meanFlowFilter.output ( &mesh_out );
    meanFlowFilter.execute();
    
    PLYDataWriter writer;
    writer.set ( &mesh_out );
    std::stringstream name;
    name <<  step << "-" << argv[2];
    writer.write( name.str().c_str() );
    return 0;
}

