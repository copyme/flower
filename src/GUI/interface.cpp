/*=========================================================================
 *
 * Program:
 * Module:    <>
 *
 * Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
 *               Meri-nut Zago <meri_zago@hotmail.fr>
 * All rights reserved.
 * See Copyright.txt for details.
 *
 *    This software is distributed WITHOUT ANY WARRANTY; without even
 *    the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *    PURPOSE.  See the above copyright notice for more information.
 *
 = *========================================================================*/

#include <stdexcept>
#include <glm/glm.hpp>
#include <glm/core/type_vec3.hpp>
#include <glm/core/type_vec4.hpp>
#include <glm/core/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "interface.h"
#include "indexed_mesh.hpp"
#include "shaders.hpp"
#include "input.h"

const char * Interface::shaderFileVer = "../shaders/basic.vert";
const char * Interface::shaderFileFrag = "../shaders/basic.frag";

Interface::Interface()
{
    if ( !glfwInit() )
    {
        throw std::runtime_error ( "Main GUI system could not be initiated!" );
    }

    GLFWmonitor * monitor = glfwGetPrimaryMonitor ();
    if ( monitor == NULL )
    {
        throw std::runtime_error ( "Could not get information about primary monitor!" );
    }
    screen = glfwGetVideoMode ( monitor );
}

void Interface::init ()
{
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow ( screen->width / 2, screen->height / 2, "Flow studio", NULL, NULL );
    if ( !window )
    {
        glfwTerminate ();
        throw std::runtime_error ( "Window could not be created!" );
    }
    // Center window
    glfwSetWindowPos(window, ( screen->width - ( screen->width / 2 ) ) / 2, (screen->height - ( screen->height / 2 ) ) / 2 );
    /* Make the window's context current */
    glfwMakeContextCurrent ( window );

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode ( window, GLFW_STICKY_KEYS, GL_TRUE ); 
    // Enable vertical sync (on cards that support it)
    glfwSwapInterval ( 1 );
    
    glfwSetWindowSizeCallback ( window, &Input::window_size_callback );

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        throw std::runtime_error ( "The OpenGL support library initialization faild!" );
    }

    shaderProgram = STP3D::ShaderManager::loadShader ( shaderFileVer, shaderFileFrag, true );
    if ( shaderProgram == 0 )
    {
      throw std::runtime_error ( "Compilation of shaders faild!" );
    }
    
    projectionLocation = glGetUniformLocation(shaderProgram, "Projection");
    viewLocation = glGetUniformLocation(shaderProgram, "View");
    color = glGetUniformLocation(shaderProgram, "color");
    
}
int Interface::exec ( Mesh & mesh)
{
  STP3D::IndexedMesh glMesh ( mesh );
  glMesh.createVAO();
  /* Loop until the user closes the window */
  while ( !glfwWindowShouldClose ( window ) )
  {
    //Interactiion with mouse need to be trigged for each frame -- so we can not use callbacks
    Input::mouse( window, camera );
    
    /* Blender like background color */
    glClearColor ( 0.2235f, 0.2235f, 0.2235f, 0.0f );
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glUseProgram ( shaderProgram );
    
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    glm::mat4 projection = glm::perspective ( 45.0f, ( float ) width / ( float ) height, .1f, 100.f );
    glm::mat4 worldToView = glm::lookAt( camera.eye, camera.o, camera.up);
    glUniformMatrix4fv ( projectionLocation, 1, 0, glm::value_ptr ( projection ) );
    glUniformMatrix4fv ( viewLocation, 1, 0, glm::value_ptr ( worldToView ) );
    
    glEnable (GL_LINE_SMOOTH);
    glLineWidth (1.5);
    glm::vec4 colorEdges (1., 1., 1., 1. );
    glUniform4fv ( color, 1, glm::value_ptr ( colorEdges ) );
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glMesh.draw();
    
    glm::vec4 colorFaces ( .7, 0.9, 0.4, .3 );
    glUniform4fv ( color, 1, glm::value_ptr ( colorFaces ) );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    
    glDisable ( GL_DEPTH_TEST );
    glEnable ( GL_BLEND );
    glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glDepthMask( false );
    glMesh.draw();
    
    glEnable(GL_DEPTH_TEST);
    
    glUseProgram(0);
    
    /* Swap front and back buffers */
    glfwSwapBuffers ( window );
    
    /* Poll for and process events */
    glfwPollEvents();
  }
  
  glfwTerminate();
  return 0;
}