#include <iostream>
#include <cstdlib>
#include <vector>
#include "plydatareader.h"
#include "edgeextractor.h"
#include "mesh.h"
#include "plydatawriter.h"
#include "meanflowfilter.h"

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
    
    mesh_out.set_model( mesh.get_model() );
    
    //copy faces to output
    for ( unsigned int i = 0; i < mesh.face_count(); i++ )
    {
        Face face = mesh.get_face(i);
        for (unsigned int j = 0; j < face.model(); j++ )
            mesh_out.add_face_vertex(face[j]);
    }
    
    MeanFlowFilter meanFlowFilter;
    meanFlowFilter.set_step ( 0.6 );
    meanFlowFilter.input ( &mesh );
    meanFlowFilter.output ( &mesh_out );
    meanFlowFilter.execute();
    
    PLYDataWriter writer;
    writer.set ( &mesh_out );
    writer.write( argv[2] );
    return 0;
}
