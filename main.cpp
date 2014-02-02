#include <iostream>
#include <cstdlib>
#include <vector>
#include "plydatareader.h"
#include "edgeextractor.h"
#include "datastructure.h"
#include "plydatawriter.h"

int main(int argc, char *argv[])
{
    if ( argc > 3 )
    {
        std::cerr << "Please define input PLY file.";
        exit ( EXIT_FAILURE );
    }
    
    Surface surface;
    PLYDataReader reader;
    reader.set ( &surface );
    reader.read ( argv[1] );
    
    EdgeExtractor extract;
    extract.set ( &surface );
    
    extract.extract ( 0 );
    
    std::vector < Edge > const & edges = extract.get();
    
    for(int i = 0; i < edges.size(); i++ )
    {
        std::cout << edges[i].begin() << " " << edges[i].end() << std::endl;
    }
    
    PLYDataWriter writer;
    writer.set ( &surface );
    writer.write( argv[2] );
    return 0;
}
