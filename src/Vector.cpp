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

#include "Vector.h"


Vector::Vector()
{
    memset ( coords, 0, sizeof (double) * dim ); 
}

Vector::Vector(const Vertex &start, const Vertex &end)
{
    for ( unsigned int i = 0; i < dim; i++ )
        coords[i] = end[i] - start[i];
}

Vector::Vector( Vector const & vec )
{
    memcpy(coords, vec.coords, sizeof ( double ) * dim );  
}

Vector &Vector::operator =(const Vector &vec)
{
    memcpy(coords, vec.coords, sizeof ( double ) * dim );    
}
