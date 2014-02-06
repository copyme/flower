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

#ifndef POINTTESTS_H
#define POINTTESTS_H

#include <cppunit/extensions/HelperMacros.h>
#include "mesh.h"

class PointTests : public CppUnit::TestFixture
{
private:
    Mesh * mesh_;
    CPPUNIT_TEST_SUITE ( PointTests );
    CPPUNIT_TEST ( coords_int_after_construction_0 );
    CPPUNIT_TEST ( coords_double_after_construction_0 );
    CPPUNIT_TEST ( coords_double_assign_1_2_3 );
    CPPUNIT_TEST ( plus_operaror );
    CPPUNIT_TEST ( plus_assign_operaror );
    CPPUNIT_TEST ( assign_vertex_0 );
    CPPUNIT_TEST ( assign_operator );
    CPPUNIT_TEST_SUITE_END();
public:
    void coords_int_after_construction_0();
    void coords_double_after_construction_0();
    void coords_double_assign_1_2_3();
    void plus_operaror();
    void plus_assign_operaror();
    void assign_vertex_0();
    void assign_operator();
    void setUp();
    void tearDown();
};

#endif // POINTTESTS_H
