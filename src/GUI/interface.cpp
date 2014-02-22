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
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/core/type_vec3.hpp>
#include <glm/core/type_vec4.hpp>
#include <glm/core/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "interface.h"
#include "shaders.hpp"
#include "input.h"

#include "imgui.h"
#include "imguiRenderGL3.h"

const char * Interface::shaderFileVer = "../shaders/basic.vert";
const char * Interface::shaderFileFrag = "../shaders/basic.frag";
extern const unsigned char DroidSans_ttf[];
extern const unsigned int DroidSans_ttf_len;

Interface::Interface()
{
    glMesh = NULL;
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

void Interface::register_listener ( GUIListener * listener )
{
    if ( std::find ( listeners.begin(), listeners.end(), listener ) == listeners.end() )
    {
        listeners.push_back ( listener );
    }
}

void Interface::remove_listener ( GUIListener * listener )
{
    listeners.remove ( listener );
}

void Interface::init ( Mesh & mesh )
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
        throw std::runtime_error ( "The OpenGL support library initialization faild!" );
    }
    shaderProgram = STP3D::ShaderManager::loadShader ( shaderFileVer, shaderFileFrag, true );
    if ( shaderProgram == 0 )
    {
        throw std::runtime_error ( "Compilation of shaders faild!" );
    }

    if (!imguiRenderGLInit(DroidSans_ttf, DroidSans_ttf_len))
    {
        throw std::runtime_error ( "Could not init GUI renderer." );
    }

    projectionLocation = glGetUniformLocation(shaderProgram, "Projection");
    viewLocation = glGetUniformLocation(shaderProgram, "View");
    color = glGetUniformLocation(shaderProgram, "color");

    glMesh = std::shared_ptr < STP3D::IndexedMesh > ( new STP3D::IndexedMesh (mesh) );
}
void Interface::data_generated ( std::shared_ptr< Mesh > mesh )
{
    glMesh = std::shared_ptr < STP3D::IndexedMesh > ( new STP3D::IndexedMesh (*mesh) );
}

int Interface::exec ()
{
    glm::vec4 colorEdges (1., 1., 1., 1. );
    glm::vec4 colorPoints (1., 0., 0., 1. );
    glm::vec4 colorFaces ( .7, 0.9, 0.4, .1 );
    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose ( window ) )
    {
        glMesh->createVAO(); // moving it tot data_generated occurs a crash -- find a way
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

        // Draw lines of faces
        glEnable (GL_LINE_SMOOTH);
        glLineWidth (1.5);
        glUniform4fv ( color, 1, glm::value_ptr ( colorEdges ) );
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glMesh->draw();

        // Draw vertices
        glPointSize (4);
        glUniform4fv ( color, 1, glm::value_ptr ( colorPoints ) );
        glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
        glMesh->draw();

        // Draw faces
        glUniform4fv ( color, 1, glm::value_ptr ( colorFaces ) );
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        glDisable ( GL_DEPTH_TEST );
        glEnable ( GL_BLEND );
        glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glDepthMask( false );
        glMesh->draw();

        glUseProgram(0);

//////////////////////////////////////// REFACTORISATION!!!!
        // Draw UI

        unsigned char mbut = 0;
        int mscroll = 0;
        double mousex;
        double mousey;
        glfwGetCursorPos(window,&mousex, &mousey);
        mousey = height - mousey;
        int leftButton = glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_LEFT );
        if( leftButton == GLFW_PRESS )
            mbut |= IMGUI_MBUT_LEFT;

        imguiBeginFrame(mousex, mousey, mbut, mscroll);
        int logScroll = 0;
        imguiBeginScrollArea("Mean curvature flow", width - 210, height - 310, 200, 300, &logScroll);
        static float time  = 0;
        imguiSlider("Time", &time, 0.0, 44.5, 0.001);
        if ( imguiButton("Jump to time!") )
        {
            std::list < GUIListener * >::iterator it = listeners.begin();
            for ( ; it != listeners.end(); ++it )
            {
                (*it)->time_changed(time);
            }
        }
        char text[50];
        sprintf(text,"Save to %1.2f-flow.ply",time);
        imguiButton(text);
        imguiEndScrollArea();
        imguiEndFrame();
        imguiRenderGLDraw(width, height);

        glDisable(GL_BLEND);
///////////////////////////////////////

        glEnable(GL_DEPTH_TEST);

        /* Swap front and back buffers */
        glfwSwapBuffers ( window );

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}