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
#include "datastructure.h"

//! This class allows to extract edges which contain a given vertex from faces
class EdgeExtractor
{
private:
    Surface const * surface;
    std::vector < Edge > edges;
public:
    EdgeExtractor();
    void set( Surface const * surface );
    
    /** \param index of a given vertex
     * \return indexes of vertices which are an end of edges which have a beginning in \param index
     */
    void extract( unsigned int index );
    std::vector < Edge > const & get() const { return edges; }
};

#endif // EDGEEXTRACTOR_H
