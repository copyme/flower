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

#ifndef MESH_H
#define MESH_H
#include <vector>

class Vertex
{
public:
    typedef std::vector < float >::const_iterator CVertexIterator;
private:   
    CVertexIterator begin;
    CVertexIterator end;
public:
    Vertex ( CVertexIterator begin, CVertexIterator end );
    float x() const { return *begin; }
    float y() const { return *(begin + 1); }
    float z() const { return *(end - 1); }
    float operator[] ( unsigned int index ) const;
};

class Edge
{
public:
    typedef std::vector < unsigned int >::const_iterator CEdgeAccessor;
private:
    CEdgeAccessor _begin;
    CEdgeAccessor _end;
public:
    Edge ( CEdgeAccessor _begin, CEdgeAccessor _end ) { this->_begin = _begin; this->_end = _end; }
    unsigned int begin() const { return *_begin; }
    unsigned int end() const { return *_end; }
};

class EdgeExtractor;

class Face
{
public:
    typedef std::vector < unsigned int >::const_iterator CFaceIterator;
private:
    CFaceIterator _begin;
    CFaceIterator _end;
    unsigned int _model;
protected:
    CFaceIterator begin() const { return _begin; }
    CFaceIterator end() const { return _end; }
public:
    Face ( CFaceIterator _begin, CFaceIterator _end, unsigned int model );
    unsigned int model() const { return _model; }
    unsigned int operator[] ( unsigned int index ) const;
    /**
     * I am unhappy with this strange construction but I have to hide begin() and 
     * end()
     */
    friend class EdgeExtractor;
};

class Mesh
{
    
public:
    std::vector < float > vertices;
    std::vector < unsigned int > faces;
    unsigned int face_model;
public:
    Mesh() { face_model = -1; }
    /*** Coordinates are evenly stored in memory - only 3-dim vertices are supported!
     * \param coord - vertex coord e.g. x, y, z
     */
    void add_vertex_coord ( float coord )
    {
        vertices.push_back ( coord );        
    }
    /*** Indexes of vertices -- each shape has to be the same size
     * \param index - index of vertex
     */
    void add_face_vertex ( unsigned int index )
    {
        faces.push_back ( index );
    }
    unsigned int get_model () const { return face_model; }
    void set_model ( unsigned int model ) { this->face_model = model; }
    unsigned int vertex_count () const { return vertices.size() / 3; }
    unsigned int face_count () const { return faces.size() / face_model; }
    Vertex get_vertex ( unsigned int index ) const;
    Face get_face ( unsigned int index ) const;
    void verify();
};

#endif // MESH_H
