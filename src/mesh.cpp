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

#include <stdexcept>
#include <algorithm>
#include "mesh.h"
#include "Vector.h"

Vertex::Vertex(CVertexIterator begin, CVertexIterator end)
{
    if ( std::distance (  begin, end ) != 3 )
    {
        throw std::runtime_error ( "Only 3-dim vertices are supported!" );
    }

    this->begin = begin;
    this->end = end;
}

float Vertex::operator [] ( unsigned int index ) const
{
    if ( index > 2 )
    {
        throw std::range_error ( "Index out of range!" );
    }
    return *(begin + index);
}

Edge::Edge ( CEdgeAccessor _begin, CEdgeAccessor _end )
{
    this->_begin = _begin;
    this->_end = _end;
    faces.first = faces.second = -1;
}
void Edge::add_face ( unsigned int index )
{
    if ( faces.first == -1 )
        faces.first = index;
    else if ( faces.second == -1)
        faces.second = index;
    else
        throw std::runtime_error ( "Edge can not belongs to more then 2 faces! Mesh is not a 2-manifold!" );
}


Face::Face ( CFaceIterator begin, CFaceIterator end, unsigned int model )
{
    if ( std::distance ( begin, end ) != model )
    {
        throw std::runtime_error ( "Model of the face and range of vertices is different!" );
    }

    this->_begin = begin;
    this->_end = end;
    this->_model = model;
}

unsigned int Face::operator[] ( unsigned int index ) const
{
    if ( index > _model - 1 )
    {
        throw std::range_error ( "Index out of range!" );
    }
    return *(_begin + index);
}

Vertex Mesh::get_vertex ( unsigned int index ) const
{
    int vertex_count = vertices.size() / 3;

    if ( index > vertex_count )
    {
        throw std::range_error ( "Index over the range of vertices!" );
    }

    Vertex::CVertexIterator begin = vertices.cbegin() + ( index * 3);
    Vertex::CVertexIterator end = begin + 3;

    return Vertex ( begin, end );
}

Face Mesh::get_face ( unsigned int index ) const
{
    int face_count = faces.size() / face_model;

    if ( index > face_count )
    {
        throw std::range_error ( "Index over the range of faces!" );
    }

    Face::CFaceIterator begin = faces.begin() + ( index * face_model );
    Face::CFaceIterator end = begin + face_model;

    return Face ( begin, end, face_model );
}

Vector < float > Mesh::get_normal ( unsigned int index ) const
{
    int normals_count = normals.size() / 3;

    if ( index > normals_count )
    {
        throw std::range_error ( "Normal over the range of normals!" );
    }
    std::vector < float >::const_iterator begin = normals.begin() + ( index * 3);
    Vector < float > _vector;
    _vector[0] = *begin;
    _vector[1] = *(begin+1);
    _vector[2] = *(begin+2);
    return _vector;
}

void Mesh::verify()
{
    if ( face_model == -1 )
        throw std::runtime_error ( "Face's model was not set!");
    if ( vertices.size() % 3 != 0 )
        throw std::runtime_error ( "Not all vertisies were fully added!" );
    if ( faces.size() % face_model != 0 )
        throw std::runtime_error ( "According to given model not all faces were fully added!" );
}

void Mesh::set_star_of( unsigned int p, std::vector< Edge > const & edges )
{
    std::vector< Edge >::const_iterator it = edges.begin();
    std::vector< Edge >::const_iterator end = edges.end();
    for ( ; it != end; ++it )
    {
        if ( (*it).begin() == p )
        {
            stars.insert( std::pair< unsigned int, Edge >( p, *it ) );
        }
    }
}
