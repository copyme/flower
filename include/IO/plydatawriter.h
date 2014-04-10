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

#ifndef PLYDATAWRITER_H
#define PLYDATAWRITER_H
#include <vector>
#include "rply.h"
#include "mesh.h"

/**
 * \brief The PLYDataWriter class provide an interface to write instance of a class \ref Mesh as PLY file.
 */
class PLYDataWriter
{
private:
    Mesh const * mesh;
    void write_header ( p_ply oply );
    void write_vertices ( p_ply oply );
    void write_faces ( p_ply oply );
public:
    PLYDataWriter();
    //! Set a mesh to write as PLY
    void set ( Mesh  const *  mesh );
    //! Write a PLY file on the hard drive
    void write ( const char * filename );
};

#endif // PLYDATAWRITER_H
