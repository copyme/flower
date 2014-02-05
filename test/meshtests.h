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

#ifndef MESHTESTS_H
#define MESHTESTS_H

#include "mesh.h"
#include <cppunit/extensions/HelperMacros.h>

class MeshTests : public CppUnit::TestFixture
{
private:
    Mesh * mesh;
    CPPUNIT_TEST_SUITE ( MeshTests );
    CPPUNIT_TEST ( vertex_Coords_Methods );
    CPPUNIT_TEST ( vertex_Coords_Indexes );
    CPPUNIT_TEST ( face_indexes );
    CPPUNIT_TEST ( number_vertex );
    CPPUNIT_TEST ( number_face );    
    CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void vertex_Coords_Methods();
  void vertex_Coords_Indexes();
  void face_indexes();
  void number_vertex();
  void number_face();
};

#endif // MESHTESTS_H
