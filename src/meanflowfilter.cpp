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
#include "point.h"

void MeanFlowFilter::execute()
{
    assert ( mesh_in != NULL );
    assert ( mesh_out != NULL );

    for ( unsigned int i = 0; i < mesh_in->vertex_count(); i++ )
    {
        Vector < float > vector;
        vector = calculate_vector ( i );
        Point < float > point ( mesh_in->get_vertex ( i ) );
	point += vector;
        mesh_out->add_vertex_coord ( point[0] );
        mesh_out->add_vertex_coord ( point[1] );
        mesh_out->add_vertex_coord ( point[2] );
    }
}

Vector < float > MeanFlowFilter::calculate_vector( unsigned int point )
{
    Vector < float > vector;
    
    std::pair< Mesh::StarConstIter, Mesh::StarConstIter > range = mesh_in->get_start ( point );
    
    Mesh::StarConstIter it = range.first;
    Mesh::StarConstIter end = range.second;
    for ( ; it != end; ++it )
    {
        if ( it->first == point )
        {
            Vector < float > N1 = mesh_in->get_normal( it->second.get_faces().first );
            Vector < float > N2 = mesh_in->get_normal( it->second.get_faces().second );
            float theta = std::acos( N1.dot( N2 ) / ( N1.length() * N2.length() ) );
            if ( std::isnan ( theta ) )
                theta = 0.f;
            Vector < float > N_E = ( N1 + N2 ) / ( 2.f * std::cos ( theta / 2.f ) );

            Vertex end = mesh_in->get_vertex ( point );
            Vertex start = mesh_in->get_vertex ( it->second.end() );
            Vector < float > tmpVector ( start, end );

            N_E *= tmpVector.length() * std::sin( theta / 2.f );
            vector += N_E;
        }
    }
    vector *= -0.5f;
    vector *= step;
    return vector;
}
