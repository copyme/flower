/*=========================================================================
  
  Program:   
  Module:    <>
  
  Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
  All rights reserved.
  See Copyright.txt for details.
  
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
     
=========================================================================*/

#include "meanflowfilter.h"
#include "edgeextractor.h"
#include "point.h"
#include <iostream>

std::vector<Vector> MeanFlowFilter::calculate_vector( std::vector<Edge> const &edges, unsigned int point)
{
   std::vector< Edge >::const_iterator it = edges.begin();
   std::vector< Edge >::const_iterator end = edges.end();
   std::vector<Vector > out;
   for ( ; it != end; ++it )
   {
       if ( (*it).begin() == point )
       {
          Vertex start = mesh_in->get_vertex ( point );
          Vertex end = mesh_in->get_vertex ( (*it).end() );
          Vector vec ( start, end );
          vec /= vec.length();
          out.push_back ( vec );
       }
   }
   return out;
}

void MeanFlowFilter::execute()
{
    EdgeExtractor extractor;
    extractor.set ( mesh_in );
    for ( unsigned int i = 0; i < mesh_in->vertex_count(); i++ )
    {
        extractor.extract ( i );
        std::vector<Vector > vec = calculate_vector ( extractor.get(), i );
        Vector vector;
        for ( unsigned int j = 0; j < vec.size(); j++ )
        {
            vector += vec[j];
        }
        vector /= vector.length();
        vector *= .4;
        Point < > point ( mesh_in->get_vertex ( i ) );
        point += vector;
        mesh_out->add_vertex_coord ( point[0] );
        mesh_out->add_vertex_coord ( point[1] );
        mesh_out->add_vertex_coord ( point[2] );
    }
}


