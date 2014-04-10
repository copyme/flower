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

#ifndef EDGEEXTRACTOR_H
#define EDGEEXTRACTOR_H
#include <vector>
#include "mesh.h"

//! This class allows to extract edges which contain a given vertex from faces
class EdgeExtractor
{
private:
    const Mesh *mesh;
    std::vector < Edge > edges;
    void init_faces ( Edge & t_edge, unsigned int i );
public:
    EdgeExtractor();
    void init( const Mesh *mesh );

    /** \param index of a given vertex
     */
    void extract( unsigned int index );
    //! \return edges which contain a vertex given as input to \ref extract( unsigned int index ) function
    std::vector < Edge > const & get() const {
        return edges;
    }

};

#endif // EDGEEXTRACTOR_H
