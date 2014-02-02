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

#include <cstddef>
#include <cassert>
#include <stdexcept>
#include "IO/rply.h"
#include "plydatawriter.h"

PLYDataWriter::PLYDataWriter()
{
    surface = NULL;
}

void PLYDataWriter::set( Surface  const *  surface )
{
    assert ( surface != NULL );
    this->surface = surface;
}

void PLYDataWriter::write ( const char * filename )
{
    assert ( surface != NULL );
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
    ply_add_element ( oply, "vertex", surface->vertex_count() );
    ply_add_scalar_property(oply, "x", PLY_FLOAT );
    ply_add_scalar_property(oply, "y", PLY_FLOAT );
    ply_add_scalar_property(oply, "z", PLY_FLOAT );
    
    ply_add_element ( oply, "face", surface->faces_count() );
    ply_add_list_property ( oply, "vertex_index", PLY_UCHAR, PLY_INT );
    ply_write_header ( oply );    
}

void PLYDataWriter::write_vertices ( p_ply oply )
{
    Surface::CVertexIterator ivertex = surface->vertices_cbegin();
    Surface::CVertexIterator ivend = surface->vertices_cend();
    for( ; ivertex != ivend; ++ivertex )
    {
          ply_write ( oply, ivertex->x );
          ply_write ( oply, ivertex->y );
          ply_write ( oply, ivertex->z );
    }
}

void PLYDataWriter::write_faces ( p_ply oply )
{
    Surface::CFaceIterator iface = surface->faces_cbegin();
    Surface::CFaceIterator ifend = surface->faces_cend();
    for( ; iface != ifend; ++iface )
    {
        ply_write ( oply, iface->size() );
        for ( int j = 0; j < iface->size(); j++ )
        {
            ply_write ( oply, (*iface)[j] );
        }
    }
}
