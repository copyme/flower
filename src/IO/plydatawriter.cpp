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

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include "IO/rply.h"
#include "plydatawriter.h"

PLYDataWriter::PLYDataWriter()
{
    mesh = NULL;
}

void PLYDataWriter::set(const test::Mesh *mesh )
{
    assert ( mesh != NULL );
    this->mesh = mesh;
}

void PLYDataWriter::write ( const char * filename )
{
    assert ( mesh != NULL );
    p_ply oply;
    oply = ply_create( filename, PLY_ASCII, NULL, 0, NULL );
    
    if ( oply == NULL )
    {
        throw std::runtime_error( "Access to output file was impossible." );
    }
    write_header ( oply );
    write_vertices ( oply );
    write_faces ( oply );
    ply_close ( oply );
}

void PLYDataWriter::write_header(p_ply oply)
{
    ply_add_element ( oply, "vertex", mesh->vertex_count() );
    ply_add_scalar_property(oply, "x", PLY_FLOAT );
    ply_add_scalar_property(oply, "y", PLY_FLOAT );
    ply_add_scalar_property(oply, "z", PLY_FLOAT );
    
    ply_add_element ( oply, "face", mesh->face_count() );
    ply_add_list_property ( oply, "vertex_index", PLY_UCHAR, PLY_INT );
    ply_write_header ( oply );    
}

void PLYDataWriter::write_vertices ( p_ply oply )
{
    for( unsigned int i = 0; i <  mesh->vertex_count(); i++ )
    {
          test::Vertex vert = mesh->get_vertex( i );
          ply_write ( oply, vert.x() );
          ply_write ( oply, vert.y() );
          ply_write ( oply, vert.z() );
    }
}

void PLYDataWriter::write_faces ( p_ply oply )
{
    for( unsigned int i = 0; i <  mesh->face_count(); i++ )
    {
        test::Face face = mesh->get_face( i );
        ply_write ( oply, face.model() );
        for ( int j = 0; j < face.model(); j++ )
        {
            ply_write ( oply, face[j] );
        }
    }
}
