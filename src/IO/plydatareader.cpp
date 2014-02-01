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
#include <iostream>
#include <cstdio>
#include "plydatareader.h"

PLYDataReader::PLYDataReader()
{
}

void PLYDataReader::read_data(const char *filename)
{
    vertices.clear();
    faces.clear();
    
    p_ply t_ply_file = NULL;
    t_ply_file = ply_open(filename, NULL, 0, NULL);
    if ( t_ply_file == NULL )
    {
        return; // We will get std error message from RPLy.
    }
    check_file(t_ply_file);
    map_vertices_callbacks(t_ply_file);
    map_faces_callbacks(t_ply_file);
    
    if ( !ply_read( t_ply_file ) )
    {
        throw std::runtime_error("Error occurred. Reading a PLY file was interrupted!");
    }
    ply_close ( t_ply_file );
 
#ifndef NDEBUG
//    std::cout << "Verices: " << std::endl;
//    for(int i = 0; i < vertices.size(); i++ )
//        std::cout << vertices[i].x << vertices[i].y << vertices[i].z << std::endl;
    
//    std::cout << "Faces: " << std::endl;
//    for(int i = 0; i < faces.size(); i++ )
//    {
//        for (int j = 0; j < faces[i].size(); j++ )
//            std::cout << faces[i][j];
//        std::cout << std::endl;
//    }
#endif
}

void PLYDataReader::check_file(p_ply file)
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
    std::vector < Vertex > * list = NULL;
    void * data_mapper = NULL;
    ply_get_argument_user_data ( argument, &data_mapper, &eol );
    list = reinterpret_cast < std::vector < Vertex > * > ( data_mapper );
    
    if ( eol == 0 ) 
    {
        Vertex vertex;
        vertex.x = ply_get_argument_value ( argument );
        list->push_back(vertex);
    }
    else if ( eol == 1 )
    {
        Vertex * vertex;
        vertex = &list->back();
        vertex->y = ply_get_argument_value ( argument );
    } 
    else if ( eol == 2 )
    {
        Vertex * vertex;
        vertex = &list->back();
        vertex->z = ply_get_argument_value ( argument );
    }
    else
        return 0;
    return 1;
}

void PLYDataReader::map_vertices_callbacks(p_ply t_ply_file)
{
    ply_set_read_cb ( t_ply_file, "vertex", "x", vertex_callback, (void *)(&vertices), 0 );
    ply_set_read_cb ( t_ply_file, "vertex", "y", vertex_callback, (void *)(&vertices), 1 );
    ply_set_read_cb ( t_ply_file, "vertex", "z", vertex_callback, (void *)(&vertices), 2 );    
}

//! \todo move to different compilation unit
static int face_callback ( p_ply_argument argument )
{
    long length = 0, value_index = -2;
    std::vector < Face > * list = NULL;
    void * data_mapper = NULL;
    ply_get_argument_user_data ( argument, &data_mapper, NULL );
    ply_get_argument_property ( argument, NULL, &length, &value_index );
    list = reinterpret_cast < std::vector < Face > * > ( data_mapper );
    
    if( value_index == 0 )
    {
        Face face;
        double vertex_index = ply_get_argument_value ( argument );
        face.add_vertex(vertex_index);
        list->push_back ( face );
    }
    else if ( value_index > 0 && value_index < length )
    {
        Face *face = &list->back();
        double vertex_index = ply_get_argument_value ( argument );
        face->add_vertex ( vertex_index );
    }
    return 1;
}

void PLYDataReader::map_faces_callbacks(p_ply t_ply_file)
{
    ply_set_read_cb(t_ply_file, "face", "vertex_indices", face_callback, (void *)(&faces), 0);
    ply_set_read_cb(t_ply_file, "face", "vertex_index", face_callback, reinterpret_cast < void * > (&faces), 0);    
}
