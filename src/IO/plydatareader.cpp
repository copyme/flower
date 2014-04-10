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
    mesh = NULL;
}

void PLYDataReader::set ( Mesh *mesh )
{
    assert ( mesh != NULL );
    this->mesh = mesh;
}

void PLYDataReader::read ( const char *filename )
{
    assert ( mesh != NULL );

    p_ply t_ply_file = NULL;
    t_ply_file = ply_open ( filename, NULL, 0, NULL);
    if ( t_ply_file == NULL )
    {
        throw std::runtime_error( "Error occurred. Reading a PLY file not found!" );
    }
    check_file(t_ply_file);
    map_callbacks_vertices(t_ply_file);
    map_callbacks_faces(t_ply_file);

    if ( !ply_read( t_ply_file ) )
    {
        throw std::runtime_error( "Error occurred. Reading a PLY file was interrupted!" );
    }
    ply_close ( t_ply_file );

#ifndef NDEBUG
//    mesh->verify();
//    std::cout << "PLYDataReader -- DEBUG REPORT " << std::endl;
//    std::cout << "Verices: " << std::endl;

//    for ( unsigned int i = 0 ; i < mesh->vertex_count(); i++ )
//    {
//        Vertex vert = mesh->get_vertex( i );
//        std::cout << vert.x() << " " << vert.y() << " " << vert.z() << std::endl;
//    }

//    std::cout << "Faces: " << std::endl;

//    for ( unsigned int i = 0 ; i < mesh->face_count(); i++  )
//    {
//        Face face = mesh->get_face ( i );
//        for (int j = 0; j < face.model(); j++ )
//        {
//            std::cout << face[j];
//        }
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
        throw std::runtime_error ( "Header of the file is not correct!" );
    }

    nvertices = ply_set_read_cb ( file, "vertex", "x", NULL, NULL, 0 );
    if ( nvertices == 0 )
    {
        throw std::runtime_error ( "PLY does not contain vertices!" );
    }

    nvfaces = ply_set_read_cb ( file, "face", "vertex_index", NULL, NULL, 0 );
    if ( nvertices == 0 )
    {
        throw std::runtime_error ( "PLY does not contain faces!" );
    }
}


//! \todo move to different compilation unit
static int vertex_callback ( p_ply_argument argument )
{
    long eol;
    Mesh * mesh = NULL;
    void * data_mapper = NULL;
    ply_get_argument_user_data ( argument, &data_mapper, &eol );
    mesh = reinterpret_cast < Mesh * > ( data_mapper );
    double value = ply_get_argument_value ( argument );
    mesh->add_vertex_coord ( value );
    return 1;
}

void PLYDataReader::map_callbacks_vertices(p_ply t_ply_file)
{
    ply_set_read_cb ( t_ply_file, "vertex", "x", vertex_callback, reinterpret_cast < void * >( mesh ), 0 );
    ply_set_read_cb ( t_ply_file, "vertex", "y", vertex_callback, reinterpret_cast < void * >( mesh ), 1 );
    ply_set_read_cb ( t_ply_file, "vertex", "z", vertex_callback, reinterpret_cast < void * >( mesh ), 2 );
}

//! \todo move to different compilation unit
static int face_callback ( p_ply_argument argument )
{
    long length = 0, value_index = -2;
    Mesh * mesh = NULL;
    void * data_mapper = NULL;
    ply_get_argument_user_data ( argument, &data_mapper, NULL );
    ply_get_argument_property ( argument, NULL, &length, &value_index );
    mesh = reinterpret_cast < Mesh * > ( data_mapper );

    if( value_index == -1 )
    {
        double model = ply_get_argument_value ( argument );
        if ( mesh->get_model() == -1 )
            mesh->set_model( model );
        else if ( mesh->get_model() != model )
            throw std::runtime_error ( "Can't work with faces of diffrent models!" );
    }
    else
    {
        double vertex_index = ply_get_argument_value ( argument );
        mesh->add_face_vertex ( vertex_index );
    }
    return 1;
}

void PLYDataReader::map_callbacks_faces(p_ply t_ply_file)
{
    ply_set_read_cb(t_ply_file, "face", "vertex_indices", face_callback, reinterpret_cast < void * >( mesh ), 0);
    ply_set_read_cb(t_ply_file, "face", "vertex_index", face_callback, reinterpret_cast < void * >( mesh ), 0);
}
