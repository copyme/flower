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

#ifndef PLYDATAREADER_H
#define PLYDATAREADER_H
#include <vector>
#include "IO/rply.h"
#include "datastructure.h"

class PLYDataReader
{
private:
    std::vector < Vertex > vertices;
    std::vector < Face > faces;
    
    void check_file( p_ply file );
    void map_vertices_callbacks(p_ply t_ply_file);
    void map_faces_callbacks(p_ply t_ply_file);
public:
    PLYDataReader ();
    void read_data ( const char * filename );
    std::vector < Vertex > const & get_vertices() const { return vertices; }
    std::vector < Face > const & get_faces() const { return faces; }    
};

#endif // PLYDATAREADER_H
