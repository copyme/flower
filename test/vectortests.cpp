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

#include "vectortests.h"
#include "Vector.h"
#include "point.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( VectorTests );


void VectorTests::vector_index_0()
{
    Vector < > vec;
    CPPUNIT_ASSERT ( vec[0] == 0 );
    CPPUNIT_ASSERT ( vec[1] == 0 );
    CPPUNIT_ASSERT ( vec[2] == 0 );
}

void VectorTests::vector_assign_123()
{
    Vector < > vec;
    vec[0] = 1.;
    vec[1] = 2.;
    vec[2] = 3.;
    CPPUNIT_ASSERT ( vec[0] == 1. );
    CPPUNIT_ASSERT ( vec[1] == 2. );
    CPPUNIT_ASSERT ( vec[2] == 3. );
}

void VectorTests::create_from_points()
{
    Point < double, 3 > point;

    point[0] = 1.;
    point[1] = 2.;
    point[2] = 3.;

    Point < double, 3 > point2;

    point2[0] = 1.;
    point2[1] = 2.;
    point2[2] = 3.;

    Vector < > vec(point, point2);
    CPPUNIT_ASSERT ( vec[0] == 0. );
    CPPUNIT_ASSERT ( vec[1] == 0. );
    CPPUNIT_ASSERT ( vec[2] == 0. );
}
