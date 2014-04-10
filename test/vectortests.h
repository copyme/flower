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

#ifndef VECTORTESTS_H
#define VECTORTESTS_H

#include <cppunit/extensions/HelperMacros.h>

class VectorTests : public CppUnit::TestFixture
{
private:
    CPPUNIT_TEST_SUITE ( VectorTests );
    CPPUNIT_TEST ( vector_index_0 );
    CPPUNIT_TEST ( vector_assign_123 );
    CPPUNIT_TEST ( create_from_points );
    CPPUNIT_TEST_SUITE_END();
public:
    void vector_index_0();
    void vector_assign_123();
    void create_from_points();
    void setUp() {}
    void tearDown() {}
};

#endif // VECTORTESTS_H
