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

#include <iostream>
#include <cassert>
#include <cstddef>
#include "normalsfinder.h"
#include "Vector.h"

NormalsFinder::NormalsFinder()
{
    _mesh = NULL;
}

void NormalsFinder::execute()
{
    assert ( _mesh != NULL );
    for ( unsigned int i = 0; i < _mesh->face_count(); i++ )
    {
        Face face = _mesh->get_face ( i );
        Vertex middle = _mesh->get_vertex( face[1] );
        Vertex first = _mesh->get_vertex( face[0] );
        Vertex last = _mesh->get_vertex( face[2] );
        
        Vector < float > vector0 ( middle, first );
        Vector < float > vector1 ( middle, last );
        Vector < float > normal;
        normal = vector1 * vector0;
        normal /= normal.length();
        _mesh->add_normal_coord ( normal[0] );
        _mesh->add_normal_coord ( normal[1] );
        _mesh->add_normal_coord ( normal[2] );
    }
}
