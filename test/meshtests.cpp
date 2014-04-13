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

#include "meshtests.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( MeshTests );


void MeshTests::setUp()
{
    mesh = new Mesh();
    mesh->set_model( 4 );
    //0
    mesh->add_vertexs_coord(0);
    mesh->add_vertexs_coord(0);
    mesh->add_vertexs_coord(0);
    //1
    mesh->add_vertexs_coord(0);
    mesh->add_vertexs_coord(0);
    mesh->add_vertexs_coord(1);
    //2
    mesh->add_vertexs_coord(0);
    mesh->add_vertexs_coord(1);
    mesh->add_vertexs_coord(1);
    //3
    mesh->add_vertexs_coord(0);
    mesh->add_vertexs_coord(1);
    mesh->add_vertexs_coord(0);
    //4
    mesh->add_vertexs_coord(1);
    mesh->add_vertexs_coord(0);
    mesh->add_vertexs_coord(0);
    //5
    mesh->add_vertexs_coord(1);
    mesh->add_vertexs_coord(0);
    mesh->add_vertexs_coord(1);
    //6
    mesh->add_vertexs_coord(1);
    mesh->add_vertexs_coord(1);
    mesh->add_vertexs_coord(1);
    //7
    mesh->add_vertexs_coord(1);
    mesh->add_vertexs_coord(1);
    mesh->add_vertexs_coord(0);

    //0
    mesh->add_face_vertex ( 0 );
    mesh->add_face_vertex ( 1 );
    mesh->add_face_vertex ( 2 );
    mesh->add_face_vertex ( 3 );

    //1
    mesh->add_face_vertex ( 7 );
    mesh->add_face_vertex ( 6 );
    mesh->add_face_vertex ( 5 );
    mesh->add_face_vertex ( 4 );

    //2
    mesh->add_face_vertex ( 0 );
    mesh->add_face_vertex ( 4 );
    mesh->add_face_vertex ( 5 );
    mesh->add_face_vertex ( 1 );

    //3
    mesh->add_face_vertex ( 1 );
    mesh->add_face_vertex ( 5 );
    mesh->add_face_vertex ( 6 );
    mesh->add_face_vertex ( 2 );

    //4
    mesh->add_face_vertex ( 2 );
    mesh->add_face_vertex ( 6 );
    mesh->add_face_vertex ( 7 );
    mesh->add_face_vertex ( 3 );

    //5
    mesh->add_face_vertex ( 3 );
    mesh->add_face_vertex ( 7 );
    mesh->add_face_vertex ( 4 );
    mesh->add_face_vertex ( 0 );
}

void MeshTests::vertex_Coords_Methods()
{
    Vertex vert = mesh->get_vertex(0);
    CPPUNIT_ASSERT(vert.x() == 0);
    CPPUNIT_ASSERT(vert.y() == 0);
    CPPUNIT_ASSERT(vert.z() == 0);

    vert = mesh->get_vertex(1);
    CPPUNIT_ASSERT(vert.x() == 0);
    CPPUNIT_ASSERT(vert.y() == 0);
    CPPUNIT_ASSERT(vert.z() == 1);

    vert = mesh->get_vertex(2);
    CPPUNIT_ASSERT(vert.x() == 0);
    CPPUNIT_ASSERT(vert.y() == 1);
    CPPUNIT_ASSERT(vert.z() == 1);

    vert = mesh->get_vertex(3);
    CPPUNIT_ASSERT(vert.x() == 0);
    CPPUNIT_ASSERT(vert.y() == 1);
    CPPUNIT_ASSERT(vert.z() == 0);

    vert = mesh->get_vertex(4);
    CPPUNIT_ASSERT(vert.x() == 1);
    CPPUNIT_ASSERT(vert.y() == 0);
    CPPUNIT_ASSERT(vert.z() == 0);

    vert = mesh->get_vertex(5);
    CPPUNIT_ASSERT(vert.x() == 1);
    CPPUNIT_ASSERT(vert.y() == 0);
    CPPUNIT_ASSERT(vert.z() == 1);

    vert = mesh->get_vertex(6);
    CPPUNIT_ASSERT(vert.x() == 1);
    CPPUNIT_ASSERT(vert.y() == 1);
    CPPUNIT_ASSERT(vert.z() == 1);

    vert = mesh->get_vertex(7);
    CPPUNIT_ASSERT(vert.x() == 1);
    CPPUNIT_ASSERT(vert.y() == 1);
    CPPUNIT_ASSERT(vert.z() == 0);
}

void MeshTests::vertex_Coords_Indexes()
{
    Vertex vert = mesh->get_vertex(0);
    CPPUNIT_ASSERT(vert[0] == 0);
    CPPUNIT_ASSERT(vert[1] == 0);
    CPPUNIT_ASSERT(vert[2] == 0);

    vert = mesh->get_vertex(1);
    CPPUNIT_ASSERT(vert[0] == 0);
    CPPUNIT_ASSERT(vert[1] == 0);
    CPPUNIT_ASSERT(vert[2] == 1);

    vert = mesh->get_vertex(2);
    CPPUNIT_ASSERT(vert[0] == 0);
    CPPUNIT_ASSERT(vert[1] == 1);
    CPPUNIT_ASSERT(vert[2] == 1);

    vert = mesh->get_vertex(3);
    CPPUNIT_ASSERT(vert[0] == 0);
    CPPUNIT_ASSERT(vert[1] == 1);
    CPPUNIT_ASSERT(vert[2] == 0);

    vert = mesh->get_vertex(4);
    CPPUNIT_ASSERT(vert[0] == 1);
    CPPUNIT_ASSERT(vert[1] == 0);
    CPPUNIT_ASSERT(vert[2] == 0);

    vert = mesh->get_vertex(5);
    CPPUNIT_ASSERT(vert[0] == 1);
    CPPUNIT_ASSERT(vert[1] == 0);
    CPPUNIT_ASSERT(vert[2] == 1);

    vert = mesh->get_vertex(6);
    CPPUNIT_ASSERT(vert[0] == 1);
    CPPUNIT_ASSERT(vert[1] == 1);
    CPPUNIT_ASSERT(vert.z() == 1);

    vert = mesh->get_vertex(7);
    CPPUNIT_ASSERT(vert[0] == 1);
    CPPUNIT_ASSERT(vert[1] == 1);
    CPPUNIT_ASSERT(vert[2] == 0);
}

void MeshTests::face_indexes()
{
    Face face = mesh->get_face ( 0 );
    CPPUNIT_ASSERT ( face[0] == 0 );
    CPPUNIT_ASSERT ( face[1] == 1 );
    CPPUNIT_ASSERT ( face[2] == 2 );
    CPPUNIT_ASSERT ( face[3] == 3 );

    face = mesh->get_face ( 1 );
    CPPUNIT_ASSERT ( face[0] == 7 );
    CPPUNIT_ASSERT ( face[1] == 6 );
    CPPUNIT_ASSERT ( face[2] == 5 );
    CPPUNIT_ASSERT ( face[3] == 4 );

    face = mesh->get_face ( 2 );
    CPPUNIT_ASSERT ( face[0] == 0 );
    CPPUNIT_ASSERT ( face[1] == 4 );
    CPPUNIT_ASSERT ( face[2] == 5 );
    CPPUNIT_ASSERT ( face[3] == 1 );

    face = mesh->get_face ( 3 );
    CPPUNIT_ASSERT ( face[0] == 1 );
    CPPUNIT_ASSERT ( face[1] == 5 );
    CPPUNIT_ASSERT ( face[2] == 6 );
    CPPUNIT_ASSERT ( face[3] == 2 );

    face = mesh->get_face ( 4 );
    CPPUNIT_ASSERT ( face[0] == 2 );
    CPPUNIT_ASSERT ( face[1] == 6 );
    CPPUNIT_ASSERT ( face[2] == 7 );
    CPPUNIT_ASSERT ( face[3] == 3 );

    face = mesh->get_face ( 5 );
    CPPUNIT_ASSERT ( face[0] == 3 );
    CPPUNIT_ASSERT ( face[1] == 7 );
    CPPUNIT_ASSERT ( face[2] == 4 );
    CPPUNIT_ASSERT ( face[3] == 0 );
}

void MeshTests::number_vertex()
{
    CPPUNIT_ASSERT ( mesh->vertex_count() == 8 );
}

void MeshTests::number_face()
{
    CPPUNIT_ASSERT ( mesh->face_count() == 6 );
}

void MeshTests::tearDown()
{
    delete mesh;
}
