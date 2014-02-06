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

#ifndef POINT_H
#define POINT_H

#include <stdexcept>
#include <cstring>
#include "Vector.h"
#include "mesh.h"

template < class Type = double, unsigned int dim = 3 >
class Point
{
private:
    Type * coords;
public:
    Point() { coords = new Type[3]; memset ( coords, 0, sizeof (Type) * dim ); }
    Point ( Vertex const & vertex )
    {
        coords = new Type[dim];
        this->coords[0] = vertex[0];
        this->coords[1] = vertex[1];
        this->coords[2] = vertex[2];
    }
    
    Type & operator [] ( unsigned int index ) 
    {
        if ( index < 3 )
            return coords[index];
    }
    virtual Point < Type, dim > operator+ ( Vector & vec )
    {
        Point < Type, dim > t_point;
        for ( unsigned int i = 0; i < dim; i++ )
            t_point[i] = (*this)[i] + vec[i];
        return t_point;
    }
    virtual Point < Type, dim > & operator += ( Vector & vec )
    {
        for ( unsigned int i = 0; i < dim; i++ )
            (*this)[i] += vec[i];
        return *this;
    }
    
    virtual Point < Type, dim > & operator -= ( Vector & vec )
    {
        for ( unsigned int i = 0; i < dim; i++ )
            (*this)[i] -= vec[i];
        return *this;
    }    
    
    virtual Point < Type, dim > & operator = ( Vertex const & vertex )
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
    
    ~Point() { delete[] coords; }
};

#endif // POINT_H
