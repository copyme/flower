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
    surface = NULL;
}

void EdgeExtractor::set ( const Surface *surface )
{
    assert ( surface != NULL );
    this->surface = surface;
}

void EdgeExtractor::extract ( unsigned int index )
{
    assert ( surface != NULL );
    edges.clear();
    Surface::CFaceIterator iface = surface->faces_cbegin();
    Surface::CFaceIterator iend = surface->faces_cend();
    
    for (; iface != iend; ++iface )
    {
        for ( unsigned int j = 0; j < iface->size(); j++ )
        {
            if ( (*iface)[j] == index )
            {
                //beginning
                if ( j ==  0 )
                {
                    Edge t_edge( (*iface)[iface->size() - 1], (*iface)[j] );
                    edges.push_back(t_edge);  
                }
                //middle - left
                if( j > 0 )
                {
                    Edge t_edge ( (*iface)[j - 1], (*iface)[j] );
                    edges.push_back ( t_edge );
                }
                //middle - right
                if ( j + 1 <  iface->size() )
                {
                    Edge t_edge( (*iface)[j], (*iface)[j  + 1] );
                    edges.push_back(t_edge);
                }
                //end
                if ( j == iface->size() - 1 )
                {
                    Edge t_edge( (*iface)[j], (*iface)[0] );
                    edges.push_back(t_edge);
                }
            }
        }
    }
}
