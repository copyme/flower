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

#ifndef VECTOR_H
#define VECTOR_H

#include <stdexcept>
#include <cassert>
#include <cstring>
#include <cmath>
#include "mesh.h"

template < class Type >
class Vector
{
private:
    static const int dim = 3;
    Type coords[dim];
public:
    Vector () {
        coords[0] =  coords[1] = coords[2] = 0;
    }

    Vector ( Vertex const &start, Vertex const &end )
    {
        coords[0] = end[0] - start[0];
        coords[1] = end[1] - start[1];
        coords[2] = end[2] - start[2];
    }

    Type & operator [] ( unsigned int index )
    {
        if ( index < 3 )
            return coords[index];
    }
    //! Vector product
    Vector operator * ( Vector  & vector ) const
    {
        Vector vec;
        vec.coords[0] = ( this->coords[1] * vector.coords[2] ) - ( vector.coords[1] * this->coords[2] );
        vec.coords[1] = ( this->coords[2] * vector.coords[0] ) - ( vector.coords[2] * this->coords[0] );
        vec.coords[2] = ( this->coords[0] * vector.coords[1] ) - ( vector.coords[0] * this->coords[1] );
        return vec;
    }

    Vector & operator *= ( double value )
    {
        this->coords[0] *= value;
        this->coords[1] *= value;
        this->coords[2] *= value;
        return *this;
    }

    Vector & operator /= ( double value )
    {
        this->coords[0] /= value;
        this->coords[1] /= value;
        this->coords[2] /= value;
        return *this;
    }

    Vector operator+ ( Vector  & vector ) const
    {
        Vector vec;
        vec.coords[0] = this->coords[0] + vector.coords[0];
        vec.coords[1] = this->coords[1] + vector.coords[1];
        vec.coords[2] = this->coords[2] + vector.coords[2];
        return vec;
    }

    Vector operator / ( double value ) const
    {
        Vector vec;
        vec.coords[0] = this->coords[0] / value;
        vec.coords[1] = this->coords[1] / value;
        vec.coords[2] = this->coords[2] / value;
        return vec;
    }

    Vector & operator+= ( Vector  & vector )
    {
        this->coords[0] += vector.coords[0];
        this->coords[1] += vector.coords[1];
        this->coords[2] += vector.coords[2];
        return *this;
    }

    double length() const
    {
        double len = this->coords[0] * this->coords[0] + this->coords[1] * this->coords[1];
        len += this->coords[2] * this->coords[2];
        return std::sqrt ( len );
    }
    double dot ( Vector  & vector )
    {
        return coords[0] * vector.coords[0] + coords[1] * vector.coords[1] + coords[2] * vector.coords[2];
    }
};

#endif // VECTOR_H
