/*=========================================================================
  
  Program:   
  Module:    <>
  
  Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
                Meri-nut Zago <meri_zago@hotmail.fr>
  All rights reserved.
  See Copyright.txt for details.
  
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
     
=========================================================================*/

#include <cassert>
#include "meanflowfilter.h"
#include "edgeextractor.h"
#include "point.h"

void MeanFlowFilter::execute()
{
    assert ( mesh_in != NULL );
    assert ( mesh_out != NULL );
    
    EdgeExtractor extractor;
    extractor.set ( mesh_in );
    for ( unsigned int i = 0; i < mesh_in->vertex_count(); i++ )
    {
        extractor.extract ( i );
        Vector < double > vector;
        vector = calculate_vector ( extractor.get(), i );
        Point < double > point ( mesh_in->get_vertex ( i ) );
        point += vector;
        mesh_out->add_vertex_coord ( point[0] );
        mesh_out->add_vertex_coord ( point[1] );
        mesh_out->add_vertex_coord ( point[2] );
    }
}

Vector < double > MeanFlowFilter::calculate_vector( std::vector<Edge> const &edges, unsigned int point)
{
    Vector < double > vector;
    std::vector< Edge >::const_iterator it = edges.begin();
    std::vector< Edge >::const_iterator end = edges.end();
    for ( ; it != end; ++it )
    {
        if ( (*it).begin() == point )
        {
            Vertex start = mesh_in->get_vertex ( point );
            Vertex end = mesh_in->get_vertex ( (*it).end() );
            Vector < double > tmpVector ( start, end );
            vector += tmpVector;
        }
    }
    vector /= vector.length();
    vector *= step;
    return vector;
}

