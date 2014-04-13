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
#include <map>
#include <utility>

/**
 * @brief The Vertex class provide an efficient way to get information about each vertex from the memory of a \ref Mesh
 * In general any mesh should not be changed during computations so this class should not provide any interface which allows
 * to change memory of mesh. If you want to manipulate of Vertex params you shoud map it to the \ref Point and after that
 * create a new mesh.
 */
template < class Type >
class Vector;

class Vertex
{
public:
    typedef std::vector < float >::const_iterator CVertexIterator;
private:
    CVertexIterator begin;
    CVertexIterator end;
public:
    Vertex ( CVertexIterator begin, CVertexIterator end );
    float x() const {
        return *begin;
    }
    float y() const {
        return *(begin + 1);
    }
    float z() const {
        return *(end - 1);
    }
    float operator[] ( unsigned int index ) const;
};

/**
 * @brief The Edge class Read only interface for memory of the \Mesh
 */
class Edge
{
public:
    typedef std::vector < unsigned int >::const_iterator CEdgeAccessor;
private:
    std::pair<int,int> faces;
    CEdgeAccessor _begin;
    CEdgeAccessor _end;
public:
    bool operator== ( Edge const & rh )
    {
        if ( ( *_begin == rh.begin()  &&  *_end == rh.end() ) ||
                ( *_end == rh.begin()  &&  *_begin == rh.end() ) )
        {
            return true;
        }
        return false;
    }
    Edge ( CEdgeAccessor _begin, CEdgeAccessor _end );
    //! \return index of vertex
    unsigned int begin() const {
        return *_begin;
    }
    //! \return index of vertex
    unsigned int end() const {
        return *_end;
    }
    void add_face( unsigned int index );
    //! \return - A pair of indices of faces. -1 on on given position if face not assigned.
    std::pair < int, int > const & get_faces() const {
        return faces;
    }
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
    CFaceIterator begin() const {
        return _begin;
    }
    CFaceIterator end() const {
        return _end;
    }
public:
    Face ( CFaceIterator _begin, CFaceIterator _end, unsigned int model );
    unsigned int model() const {
        return _model;
    }
    unsigned int operator[] ( unsigned int index ) const;
    /*
     * I am unhappy with this strange construction but I have to hide begin() and
     * end()
     */
    friend class EdgeExtractor;
};

template < class Type >
class Vector;
namespace STP3D {
class IndexedMesh;    // Predefinition of a decorator;
}

class Mesh
{
private:
    friend class STP3D::IndexedMesh; // For decorator which can show mesh using OpenGL
    std::vector < float > vertices;
    std::vector < unsigned int > faces;
    std::vector < float > normals;
    /***
     * Key -- vertex
     * Values -- vertices which create edges with a vertex defined by Key
     *
     */
    std::multimap< unsigned int, Edge > stars;
    unsigned int face_model;
public:
    typedef std::multimap < unsigned int, Edge >::const_iterator StarConstIter;
    Mesh() {
        face_model = -1;
    }
    /*** Coordinates are evenly stored in memory - only 3-dim vertices are supported!
     * \param coord - vertex coord e.g. x, y, z
     */
    void add_vertexs_coord ( float coord )
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
    unsigned int get_model () const {
        return face_model;
    }
    void set_model ( unsigned int model ) {
        this->face_model = model;
    }
    unsigned int vertex_count () const {
        return vertices.size() / 3;
    }
    unsigned int face_count () const {
        return faces.size() / face_model;
    }
    Vertex get_vertex ( unsigned int index ) const;
    Face get_face ( unsigned int index ) const;
    void add_normals_coord ( float coord )
    {
        normals.push_back( coord );
    }
    void set_star_of( unsigned int vertex, std::vector< Edge > const & edges );
    std::pair< StarConstIter, StarConstIter > get_start ( unsigned int vertex ) const {
        return stars.equal_range( vertex );
    }
    void copy_faces( const Mesh * mesh ) {
        std::copy( mesh->faces.begin(), mesh->faces.end(), std::back_inserter( this->faces ) );
    }
    //! \param index - index of face
    Vector < float > get_normal ( unsigned int index ) const;
    unsigned int normal_count () const {
        return normals.size () / 3;
    }
    void clear_vertices() { vertices.clear(); };
    void verify();
};

#endif // MESH_H
