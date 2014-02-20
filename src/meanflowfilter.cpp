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
#include <cmath>
#include "meanflowfilter.h"
#include "edgeextractor.h"
#include "point.h"

void MeanFlowFilter::execute()
{
    assert ( mesh_in != NULL );
    assert ( mesh_out != NULL );
    
    EdgeExtractor extractor;
    extractor.init ( mesh_in );
    for ( unsigned int i = 0; i < mesh_in->vertex_count(); i++ )
    {
        extractor.extract ( i );
        Vector < float > vector;
        vector = calculate_vector ( extractor.get(), i );
        Point < float > point ( mesh_in->get_vertex ( i ) );
        point += vector;
        mesh_out->add_vertex_coord ( point[0] );
        mesh_out->add_vertex_coord ( point[1] );
        mesh_out->add_vertex_coord ( point[2] );
    }
}

Vector < float > MeanFlowFilter::calculate_vector( std::vector<Edge> const &edges, unsigned int point)
{
    Vector < float > vector;
    std::vector< Edge >::const_iterator it = edges.begin();
    std::vector< Edge >::const_iterator end = edges.end();
    for ( ; it != end; ++it )
    {
        if ( (*it).begin() == point )
        {
            Vector < float > N1 = mesh_in->get_normal( it->get_faces().first );
            Vector < float > N2 = mesh_in->get_normal( it->get_faces().second );
            double theta = N1.dot( N2 ) / ( N1.length() * N2.length() );
            if ( theta == 0. )
                theta = M_2_PI;
            Vector < float > N_E = ( N1 + N2 ) / ( 2. * std::cos ( theta / 2. ) );
            
            Vertex end = mesh_in->get_vertex ( point );
            Vertex start = mesh_in->get_vertex ( (*it).end() );
            Vector < float > tmpVector ( start, end );
            
            N_E *= tmpVector.length() * std::sin( theta / 2. );
            vector += N_E;
        }
    }
    vector *= -0.5;
    vector *= step;
    return vector;
}
