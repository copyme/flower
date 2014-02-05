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
#include <cstddef>
#include <algorithm>
#include "edgeextractor.h"

EdgeExtractor::EdgeExtractor()
{
    mesh = NULL;
}

void EdgeExtractor::set ( const test::Mesh *mesh )
{
    assert ( mesh != NULL );
    this->mesh = mesh;
}

void EdgeExtractor::extract ( unsigned int index )
{
    assert ( mesh != NULL );
    edges.clear();
    
    for ( unsigned int i = 0; i < mesh->face_count(); i++ )
    {
        test::Face face = mesh->get_face ( i );
        for ( unsigned int j = 0; j < face.model(); j++ )
        {
            if ( face[j] == index )
            {
                //beginning
                if ( j ==  0 )
                {
                    test::Edge t_edge( face.end() - 1, face.begin()+j );
                    edges.push_back(t_edge);
                }
                //middle - left
                if( j > 0 )
                {
                    test::Edge t_edge ( face.begin() + j - 1, face.begin()+j );
                    edges.push_back ( t_edge );
                }
                //middle - right
                if ( j + 1 <  face.model() )
                {
                    test::Edge t_edge( face.begin() + j , face.begin()+ j +1 );
                    edges.push_back(t_edge);
                }
                //end
                if ( j == face.model() - 1 )
                {
                    test::Edge t_edge( face.begin()+j, face.begin() );
                    edges.push_back(t_edge);
                }
            }
        }
    }
}
