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

#ifndef NORMALSFINDER_H
#define NORMALSFINDER_H

#include "mesh.h"

class NormalsFinder
{
private:
    Mesh * _mesh;
public:
    void set( Mesh * mesh ) { _mesh = mesh; }
    void execute();
    NormalsFinder();
};

#endif // NORMALSFINDER_H
