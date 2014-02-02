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

#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <vector>

//! \todo Split 

class Vertex
{
public:
   double x;
   double y;
   double z;
   Vertex()
   {
       x = y = z = 0.;
   }
};

class Edge
{
private:
    unsigned int m_begin;
    unsigned int m_end;
public:
    Edge ( unsigned int begin, unsigned int end ) { m_begin = begin; m_end = end; }
    unsigned int begin() const { return m_begin; }
    unsigned int end() const { return m_end; }
};


class Face
{
private:
    std::vector < int > vertices;
public:
    Face(){}
    bool add_vertex ( unsigned int index );
    //! read access to indexes of vertices
    int operator[] ( unsigned int index ) const;
    int size() const { return vertices.size(); }
};

class Surface
{
private:
    std::vector < Vertex > vertices;
    std::vector < Face > faces;
public:
    typedef std::vector < Vertex >::const_iterator CVertexIterator;
    typedef std::vector < Vertex >::iterator VertexIterator;
    typedef std::vector < Face >::const_iterator CFaceIterator;
    typedef std::vector < Face >::iterator FaceIterator;
    
    Surface () {}
    CVertexIterator vertices_cbegin() const
    {
        return vertices.begin();
    }
    VertexIterator vertices_begin()
    {
        return vertices.begin();
    }
    CVertexIterator vertices_cend() const
    {
        return vertices.end();
    }
    VertexIterator vertices_end()
    {
        return vertices.end();
    }
    CFaceIterator faces_cbegin() const
    {
        return faces.begin();
    }
    FaceIterator faces_begin()
    {
        return faces.begin();
    }
    CFaceIterator faces_cend() const
    {
        return faces.end();
    }
    FaceIterator faces_end()
    {
        return faces.end();
    }
    void add_face ( Face face )
    {
        faces.push_back( face );
    }
    void add_vertex ( Vertex vertex )
    {
        vertices.push_back( vertex );
    }
    unsigned int vertex_count() const 
    {
        return vertices.size();
    }
    unsigned int faces_count() const 
    {
        return faces.size();
    }
};


#endif // DATA_STRUCTURE_H
