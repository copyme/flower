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
#include "mesh.h"
/**
 * \brief The PLYDataReader class provide an interface for reading PLY files from the hard drive.
 */
class PLYDataReader
{
private:
    Mesh * mesh;

    void check_file( p_ply file );
    void map_callbacks_vertices(p_ply t_ply_file);
    void map_callbacks_faces(p_ply t_ply_file);
public:
    PLYDataReader ();
    //! \param mesh pointer to instace of mesh class in which geometry will be stored
    void set ( Mesh * mesh );
    //! \param path to the PLY file
    void read ( const char * filename );  
};

#endif // PLYDATAREADER_H
