#include <iostream>
#include <cstdlib>
#include <vector>
#include "plydatareader.h"
#include "edgeextractor.h"
#include "flowrunner.h"

//#include "plydatawriter.h"
//#include "meanflowfilter.h"

//int main ( int argc, char *argv[] )
//{
//    if ( argc < 3 )
//    {
//        std::cerr << "Please define input and output: PLY files.\n";
//        exit ( EXIT_FAILURE );
//    }
//    Mesh mesh, mesh_out;
//    PLYDataReader reader;
//    reader.set ( &mesh );
//    reader.read ( argv[1] );
//    mesh.verify();

//    mesh_out.set_model( mesh.get_model() );

//    //copy faces to output
//    for ( unsigned int i = 0; i < mesh.face_count(); i++ )
//    {
//        Face face = mesh.get_face(i);
//        for (unsigned int j = 0; j < face.model(); j++ )
//            mesh_out.add_face_vertex(face[j]);
//    }

//    MeanFlowFilter meanFlowFilter;
//    meanFlowFilter.set_step ( .1 );
//    meanFlowFilter.input ( &mesh );
//    meanFlowFilter.output ( &mesh_out );
//    meanFlowFilter.execute();

//    PLYDataWriter writer;
//    writer.set ( &mesh_out );
//    writer.write( argv[2] );
//    return 0;
//}

#include <cstdlib>
#include <stdio.h>
#include "mesh.h"
#include "interface.h"
#include "flowrunner.h"

int main ( int argc, char *argv[] )
{
  Mesh mesh;
  PLYDataReader reader;
  reader.set ( &mesh );
  reader.read ( argv[1] );
  mesh.verify();
 
   MeanFlowFilter meanFlowFilter;
   meanFlowFilter.set_step ( .1 );
   meanFlowFilter.input ( &mesh );
  
  FlowRunner flowRunner ( meanFlowFilter );
  
  Interface interface;
  flowRunner.register_listener(&interface);
  interface.register_listener(&flowRunner);
  interface.init( mesh );

  return interface.exec();
}

