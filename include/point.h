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

#ifndef POINT_H
#define POINT_H

#include <stdexcept>
#include <cstring>
#include "Vector.h"
#include "mesh.h"

template < class Type = double >
class Point
{
private:
    static const int dim = 3;
    Type coords[dim];
public:
    Point() { memset ( coords, 0, sizeof (Type) * dim ); }
    Point ( Vertex const & vertex )
    {
        this->coords[0] = vertex[0];
        this->coords[1] = vertex[1];
        this->coords[2] = vertex[2];
    }
    
    Type & operator [] ( unsigned int index ) 
    {
        if ( index < 3 )
            return coords[index];
    }
    virtual Point < Type > operator+ ( Vector < Type > & vec )
    {
        Point < Type > t_point;
        for ( unsigned int i = 0; i < dim; i++ )
            t_point[i] = (*this)[i] + vec[i];
        return t_point;
    }
    virtual Point < Type > & operator += ( Vector < Type > & vec )
    {
        for ( unsigned int i = 0; i < dim; i++ )
            (*this)[i] += vec[i];
        return *this;
    }
    
    virtual Point < Type > & operator -= ( Vector < Type > & vec )
    {
        for ( unsigned int i = 0; i < dim; i++ )
            (*this)[i] -= vec[i];
        return *this;
    }    
    
    virtual Point < Type > & operator = ( Vertex const & vertex )
    {
        if ( dim != 3 )
        {
            throw std::runtime_error ( "Vertex can be assigned only to the 3D points!" );
        }
        this->coords[0] = vertex[0];
        this->coords[1] = vertex[1];
        this->coords[2] = vertex[2];
        return *this;
    }
};

#endif // POINT_H
