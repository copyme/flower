#include <iostream>
#include <cstdlib>
#include <vector>
#include "plydatareader.h"
#include "edgeextractor.h"
#include "datastructure.h"
#include "plydatawriter.h"

int main(int argc, char *argv[])
{
    if ( argc < 3 )
    {
        std::cerr << "Please define input and output: PLY files.\n";
        exit ( EXIT_FAILURE );
    }
    
    test::Mesh mesh;
    PLYDataReader reader;
    reader.set ( &mesh );
    reader.read ( argv[1] );
    
    EdgeExtractor edgeExtractor;
    edgeExtractor.set ( &mesh );
    
    edgeExtractor.extract ( 0 );
    
    std::vector < test::Edge > const & edges = edgeExtractor.get();
    std::cout << "Edges for vertex 0:" << std::endl;
    for(int i = 0; i < edges.size(); i++ )
    {
        std::cout << edges[i].begin() << " " << edges[i].end() << std::endl;
    }
    
    PLYDataWriter writer;
    writer.set ( &mesh );
    writer.write( argv[2] );
    return 0;
}
