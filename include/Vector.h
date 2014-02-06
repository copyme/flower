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

#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <cassert>
#include <cstring>
#include <cmath>
#include "mesh.h"

class Vector
{
private:
    static const int dim = 3;
    double coords[dim];
public:
    Vector ();
   
    Vector ( Vertex const &start, Vertex const &end );
    
    Vector ( Vector const & vec );
    
    Vector & operator = ( Vector const & vec );
    
    double & operator [] ( unsigned int index ) 
    {
        if ( index < 3 )
            return coords[index];
    }
    
    Vector operator * ( Vector  & vector ) const
    {
        Vector vec;
        vec[0] = ( this->coords[1] * vector[2] ) - ( vector[1] * this->coords[2] );
        vec[1] = ( this->coords[2] * vector[0] ) - ( vector[2] * this->coords[0] );
        vec[2] = ( this->coords[0] * vector[1] ) - ( vector[0] * this->coords[1] );
        return vec;
    }
    
    Vector & operator*= (double value)
    {
        this->coords[0] *= value;
        this->coords[1] *= value;
        this->coords[2] *= value;
        return *this;
    }
    Vector & operator/= (double value)
    {
        this->coords[0] /= value;
        this->coords[1] /= value;
        this->coords[2] /= value;
        return *this;
    }
    
    Vector operator+ ( Vector  & vector ) const
    {
        Vector vec;
        vec[0] = this->coords[0] + vector[0];
        vec[1] = this->coords[1] + vector[1];
        vec[2] = this->coords[2] + vector[2];
        return vec;
    }
    
    Vector & operator+= ( Vector  & vector )
    {
        this->coords[0] += vector[0];
        this->coords[1] += vector[1];
        this->coords[2] += vector[2];
        return *this;
    }
    
    double length() const
    {
      double len = this->coords[0] * this->coords[0] + this->coords[1] * this->coords[1];
      len += this->coords[2] * this->coords[2];
      return sqrt(len);
    }
};

#endif // VECTOR_H
