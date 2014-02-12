#include <iostream>
#include <cstdlib>
#include <vector>
#include "plydatareader.h"
#include "edgeextractor.h"
#include "mesh.h"
//#include "plydatawriter.h"
//#include "meanflowfilter.h"

//int main ( int argc, char *argv[] )
//{
//    if ( argc < 3 )
//    {
//        std::cerr << "Please define input and output: PLY files.\n";
//        exit ( EXIT_FAILURE );
//    }
//    Mesh mesh, mesh_out;
//    PLYDataReader reader;
//    reader.set ( &mesh );
//    reader.read ( argv[1] );
//    mesh.verify();
    
//    mesh_out.set_model( mesh.get_model() );
    
//    //copy faces to output
//    for ( unsigned int i = 0; i < mesh.face_count(); i++ )
//    {
//        Face face = mesh.get_face(i);
//        for (unsigned int j = 0; j < face.model(); j++ )
//            mesh_out.add_face_vertex(face[j]);
//    }
    
//    MeanFlowFilter meanFlowFilter;
//    meanFlowFilter.set_step ( .1 );
//    meanFlowFilter.input ( &mesh );
//    meanFlowFilter.output ( &mesh_out );
//    meanFlowFilter.execute();
    
//    PLYDataWriter writer;
//    writer.set ( &mesh_out );
//    writer.write( argv[2] );
//    return 0;
//}

#include <cstdlib>
#include <stdio.h>


#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include "indexed_mesh.hpp"
#include "shaders.hpp"


int main ( int argc, char *argv[] )
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Flow studio", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if ( argc < 3 )
    {
        std::cerr << "Please define input and output: PLY files.\n";
        exit ( EXIT_FAILURE );
    }

    glewExperimental=GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
          /* Problem: glewInit failed, something is seriously wrong. */
          exit( EXIT_FAILURE );
    }

    Mesh mesh;
    PLYDataReader reader;
    reader.set ( &mesh );
    reader.read ( argv[1] );
    mesh.verify();

    const char * shaderFileVer = "shaders/flat_shading.vert";
    const char * shaderFileFrag = "shaders/flat_shading.frag";


    GLuint flatShaderPrg = STP3D::ShaderManager::loadShader(shaderFileVer,shaderFileFrag,true);

    STP3D::IndexedMesh glMesh;
    if ( mesh.get_model() != 3 )
        glMesh.changeType(GL_TRIANGLE_STRIP);
    glMesh.setNbElt(mesh.face_count());
    glMesh.setNbIndex(mesh.face_count());
    glMesh.addIndexBuffer(&mesh.faces[0],false);
    glMesh.addOneBuffer(0, mesh.get_model(), &mesh.vertices[0], std::string("position"),false);
    glMesh.createVAO();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glUseProgram(flatShaderPrg);

        glMesh.draw();

        glUseProgram(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

