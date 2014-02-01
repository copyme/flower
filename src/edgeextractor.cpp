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

#include <cstddef>

#include <iostream>

#include <algorithm>
#include "edgeextractor.h"

EdgeExtractor::EdgeExtractor()
{
    faces = NULL;
}

void EdgeExtractor::extract ( unsigned int index )
{
    edges.clear();
    
    for ( unsigned int i = 0; i < faces->size(); i++ )
    {
        for ( unsigned int j = 0; j < faces->at(i).size(); j++ )
        {
            if ( faces->at(i)[j] == index )
            {
                //beginning
                if ( j ==  0 )
                {
                    Edge t_edge( faces->at(i)[faces->at(i).size() - 1], faces->at(i)[j] );
                    edges.push_back(t_edge);  
                }
                //middle - left
                if( j > 0 )
                {
                    Edge t_edge(faces->at(i)[j - 1], faces->at(i)[j] );
                    edges.push_back(t_edge);
                }
                //middle - right
                if ( j + 1 <  faces->at(i).size() )
                {
                    Edge t_edge(faces->at(i)[j], faces->at(i)[j  + 1] );
                    edges.push_back(t_edge);
                }
                //end
                if ( j == faces->at(i).size() - 1 )
                {
                    Edge t_edge(faces->at(i)[j], faces->at(i)[0] );
                    edges.push_back(t_edge);
                }
            }
        }
    }
}
