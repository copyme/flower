#include <iostream>
#include <vector>
#include "plydatareader.h"
#include "edgeextractor.h"
#include "datastructure.h"

using namespace std;

int main()
{
    PLYDataReader dd;
    dd.read_data("cube.ply");
    
    EdgeExtractor extract;
    
    std::vector < Face > const & faces = dd.get_faces();
    
    extract.set(&faces);
    
    extract.extract(5);
    
    std::vector < Edge > const & edges = extract.get();
    
    for(int i = 0; i < edges.size(); i++ )
    {
        std::cout << edges[i].begin() << " " << edges[i].end() << std::endl;
    }
    
    return 0;
}

