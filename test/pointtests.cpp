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

#include "pointtests.h"
#include "Vector.h"
#include "point.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( PointTests );

void PointTests::setUp() 
{
    mesh_ = new Mesh();
    //0
    mesh_->add_vertex_coord(1.);
    mesh_->add_vertex_coord(2.);
    mesh_->add_vertex_coord(3);    
}

void PointTests::tearDown() 
{
    delete mesh_;
}

void PointTests::coords_int_after_construction_0()
{
    Point < int, 3 > point;
    CPPUNIT_ASSERT( point[0] == 0 );
    CPPUNIT_ASSERT( point[1] == 0 );
    CPPUNIT_ASSERT( point[2] == 0 );
}

void PointTests::coords_double_after_construction_0()
{
    Point < double, 3 > point;
    CPPUNIT_ASSERT( point[0] == 0 );
    CPPUNIT_ASSERT( point[1] == 0 );
    CPPUNIT_ASSERT( point[2] == 0 );    
}

void PointTests::coords_double_assign_1_2_3()
{
    Point < double, 3 > point;
    point[0] = 1.;
    point[1] = 2.;
    point[2] = 3.;
    CPPUNIT_ASSERT( point[0] == 1. );
    CPPUNIT_ASSERT( point[1] == 2. );
    CPPUNIT_ASSERT( point[2] == 3. );     
}

void PointTests::plus_operaror()
{
  Point < double, 3 > point;
  
  point[0] = 1.;
  point[1] = 2.;
  point[2] = 3.;  
  
  Vector < double, 3 > vect;
  
  vect[0] = 2.;
  vect[1] = 3.;
  vect[2] = 4.;  
  
  Point < double, 3 > point3 = point + vect;
  
  CPPUNIT_ASSERT( point3[0] == 3. );
  CPPUNIT_ASSERT( point3[1] == 5. );
  CPPUNIT_ASSERT( point3[2] == 7. );
}

void PointTests::plus_assign_operaror()
{
    Point < double, 3 > point;
    
    point[0] = 1.;
    point[1] = 2.;
    point[2] = 3.;  
    
    Vector < double, 3 > vect;
    
    vect[0] = 2.;
    vect[1] = 3.;
    vect[2] = 4.;
    
    point += vect;
    
    CPPUNIT_ASSERT( point[0] == 3. );
    CPPUNIT_ASSERT( point[1] == 5. );
    CPPUNIT_ASSERT( point[2] == 7. );  
}

void PointTests::assign_operator()
{
    Point < double, 3 > point;
    
    point[0] = 1.;
    point[1] = 2.;
    point[2] = 3.;
    
    Point < double, 3 > point2 = point;
    
    CPPUNIT_ASSERT( point2[0] == 1. );
    CPPUNIT_ASSERT( point2[1] == 2. );
    CPPUNIT_ASSERT( point2[2] == 3. ); 
}

void PointTests::assign_vertex_0()
{
    Point < double, 3 > point;
    Vertex vert = mesh_->get_vertex ( 0 );
    point = vert;
    CPPUNIT_ASSERT( point[0] == 1. );
    CPPUNIT_ASSERT( point[1] == 2. );
    CPPUNIT_ASSERT( point[2] == 3. );      
}
