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

#include <algorithm>
#include <stdexcept>
#include "datastructure.h"

bool Face::add_vertex ( unsigned int index )
{
    if( std::find ( vertices.begin(), vertices.end(), index) == vertices.end() )
    {
        vertices.push_back ( index );
        return true;
    }
    else
        return false;
}

int Face::operator[] ( unsigned int index ) const
{
    if ( index < vertices.size() )
    {
        return vertices[index];
    }
    else 
        throw std::out_of_range("Wrong index!");
}
