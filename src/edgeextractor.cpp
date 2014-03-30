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

#include <iostream>

#include <cassert>
#include <cstddef>
#include <algorithm>
#include "edgeextractor.h"

EdgeExtractor::EdgeExtractor()
{
    mesh = NULL;
}

void EdgeExtractor::init ( const Mesh *mesh )
{
    assert ( mesh != NULL );
    this->mesh = mesh;
}

void EdgeExtractor::init_faces( Edge & t_edge, unsigned int i )
{
    t_edge.add_face ( i );
    std::vector < Edge >::iterator it = std::find(edges.begin(), edges.end(), t_edge );
    if( it == edges.end() )
        return;
    t_edge.add_face ( it->get_faces().first );
    it->add_face( i );
}

void EdgeExtractor::extract ( unsigned int index )
{
    assert ( mesh != NULL );
    edges.clear();
    for ( unsigned int i = 0; i < mesh->face_count(); i++ )
    {
        Face const face = mesh->get_face ( i );
        for ( unsigned int j = 0; j < face.model(); j++ )
        {
            if ( face[j] == index )
            {
                //beginning
                if ( j ==  0 )
                {
                    Edge t_edge( face.end() - 1, face.begin()+j );
                    init_faces(t_edge, i);
                    edges.push_back ( t_edge );
                }
                //middle - left
                if ( j > 0 )
                {
                    Edge t_edge ( face.begin() + j - 1, face.begin()+j );
                    init_faces(t_edge, i);
                    edges.push_back ( t_edge );
                }
                //middle - right
                if ( j + 1 <  face.model() )
                {
                    Edge t_edge( face.begin() + j , face.begin()+ j +1 );
                    init_faces(t_edge, i);
                    edges.push_back(t_edge);
                }
                //end
                if ( j == face.model() - 1 )
                {
                    Edge t_edge( face.begin()+j, face.begin() );
                    init_faces(t_edge, i);
                    edges.push_back(t_edge);
                }
            }
        }
    }
}
