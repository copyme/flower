#include <vector>
#include "edgeextractor.h"
#include "normalsfinder.h"
#include "mesh.h"
#include "interface.h"
#include "flowrunner.h"
#include "plydatareader.h"

int main ( int argc, char *argv[] )
{
  Mesh mesh;
  PLYDataReader reader;
  reader.set ( &mesh );
  reader.read ( argv[1] );
  mesh.verify();
  
    NormalsFinder normalsFinder;
    normalsFinder.set(&mesh);
    normalsFinder.execute();
 
   MeanFlowFilter meanFlowFilter;
   meanFlowFilter.input ( &mesh );
  
  FlowRunner flowRunner ( meanFlowFilter );
  
  Interface interface;
  flowRunner.register_listener(&interface);
  interface.register_listener(&flowRunner);
  interface.init( mesh );

  return interface.exec();
}