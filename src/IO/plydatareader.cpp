/*=========================================================================
  
  Program:   
  Module:    <plydatareader>
  
  Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>,
                Meri-nut Zago <meri_zago@hotmail.fr>
  All rights reserved.
  See Copyright.txt for details.
  
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
     
=========================================================================*/

#include <stdexcept>
#include <cassert>
#include <iostream>
#include <cstdio>
#include "plydatareader.h"

PLYDataReader::PLYDataReader()
{
    surface = NULL;
}

void PLYDataReader::set ( Surface *surface )
{
    assert ( surface != NULL );
    this->surface = surface;
}

void PLYDataReader::read ( const char *filename )
{
    assert ( surface != NULL );
    faces.clear();
    
    p_ply t_ply_file = NULL;
    t_ply_file = ply_open(filename, NULL, 0, NULL);
    if ( t_ply_file == NULL )
    {
        return; // We will get std error message from RPLy.
    }
    check_file(t_ply_file);
    map_callbacks_vertices(t_ply_file);
    map_callbacks_faces(t_ply_file);
    
    if ( !ply_read( t_ply_file ) )
    {
        throw std::runtime_error("Error occurred. Reading a PLY file was interrupted!");
    }
    ply_close ( t_ply_file );
 
#ifndef NDEBUG
//    std::cout << "Verices: " << std::endl;
    
//    Surface::CVertexIterator it = surface->vertices_cbegin();
//    Surface::CVertexIterator iend = surface->vertices_cend();
    
//    for(; it != iend; ++it )
//        std::cout << it->x << " " << it->y << " " << it->z << std::endl;
    
//    std::cout << "Faces: " << std::endl;
    
//    Surface::CFaceIterator itf = surface->faces_cbegin();
//    Surface::CFaceIterator iendf = surface->faces_cend();
    
//    for(; itf != iendf; ++itf  )
//    {
//        for (int j = 0; j < itf->size(); j++ )
//            std::cout << (*itf)[j] << " ";
//        std::cout << std::endl;
//    }
#endif
}

void PLYDataReader::check_file ( p_ply file )
{
    int nvertices = 0;
    int nvfaces = 0;
    
    if ( ply_read_header ( file ) != 1 )
    {
        throw std::runtime_error("Header of the file is not correct!");
    }
    
    nvertices = ply_set_read_cb ( file, "vertex", "x", NULL, NULL, 0 );
    if ( nvertices == 0 )
    {
        throw std::runtime_error("PLY does not contain vertices!");
    }
    
    nvfaces = ply_set_read_cb ( file, "face", "vertex_index", NULL, NULL, 0 );
    if ( nvertices == 0 )
    {
        throw std::runtime_error("PLY does not contain faces!");
    }
}


//! \todo move to different compilation unit
static int vertex_callback ( p_ply_argument argument )
{
    long eol;
    Surface * surface = NULL;
    void * data_mapper = NULL;
    ply_get_argument_user_data ( argument, &data_mapper, &eol );
    surface = reinterpret_cast < Surface * > ( data_mapper );
    if ( eol == 0 ) 
    {
        Vertex vertex;
        vertex.x = ply_get_argument_value ( argument );
        surface->add_vertex( vertex );
    }
    else if ( eol == 1 )
    {
        Surface::VertexIterator vertex = surface->vertices_end()-1;
        vertex->y = ply_get_argument_value ( argument );
    } 
    else if ( eol == 2 )
    {
        Surface::VertexIterator vertex = surface->vertices_end()-1;
        vertex->z = ply_get_argument_value ( argument );
    }
    else
        return 0;
    return 1;
}

void PLYDataReader::map_callbacks_vertices(p_ply t_ply_file)
{
    ply_set_read_cb ( t_ply_file, "vertex", "x", vertex_callback, reinterpret_cast < void * >( surface ), 0 );
    ply_set_read_cb ( t_ply_file, "vertex", "y", vertex_callback, reinterpret_cast < void * >( surface ), 1 );
    ply_set_read_cb ( t_ply_file, "vertex", "z", vertex_callback, reinterpret_cast < void * >( surface ), 2 );    
}

//! \todo move to different compilation unit
static int face_callback ( p_ply_argument argument )
{
    long length = 0, value_index = -2;
    Surface * surface = NULL;
    void * data_mapper = NULL;
    ply_get_argument_user_data ( argument, &data_mapper, NULL );
    ply_get_argument_property ( argument, NULL, &length, &value_index );
    surface = reinterpret_cast < Surface * > ( data_mapper );
    
    if( value_index == 0 )
    {
        Face face;
        double vertex_index = ply_get_argument_value ( argument );
        face.add_vertex( vertex_index );
        surface->add_face ( face );
    }
    else if ( value_index > 0 && value_index < length )
    {
        Surface::FaceIterator face = surface->faces_end()-1;
        double vertex_index = ply_get_argument_value ( argument );
        face->add_vertex ( vertex_index );
    }
    return 1;
}

void PLYDataReader::map_callbacks_faces(p_ply t_ply_file)
{
    ply_set_read_cb(t_ply_file, "face", "vertex_indices", face_callback, reinterpret_cast < void * >( surface ), 0);
    ply_set_read_cb(t_ply_file, "face", "vertex_index", face_callback, reinterpret_cast < void * >( surface ), 0);    
}
