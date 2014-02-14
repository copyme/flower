#include <iostream>
#include <cstdlib>
#include <vector>
#include "plydatareader.h"
#include "edgeextractor.h"

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

#include <glm/glm.hpp>
#include <glm/core/type_vec3.hpp>
#include <glm/core/type_vec4.hpp>
#include <glm/core/type_mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"
#include "camera.h"
#include "indexed_mesh.hpp"
#include "shaders.hpp"
#include "statemonitor.h"

int main ( int argc, char *argv[] )
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    int width = 1024, height=768;
    float widthf = (float) width, heightf = (float) height;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Flow studio", NULL, NULL);
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

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
          /* Problem: glewInit failed, something is seriously wrong. */
          exit( EXIT_FAILURE );
    }

    // Enable vertical sync (on cards that support it)
    glfwSwapInterval( 1 );

    Camera camera;
    GUIStateMonitor guiStates;

    Mesh mesh;
    PLYDataReader reader;
    reader.set ( &mesh );
    reader.read ( argv[1] );
    mesh.verify();

    const char * shaderFileVer = "../shaders/flat_shading.vert";
    const char * shaderFileFrag = "../shaders/flat_shading.frag";


    GLuint flatShaderPrg = STP3D::ShaderManager::loadShader(shaderFileVer,shaderFileFrag,true);

    GLuint projectionLocation = glGetUniformLocation(flatShaderPrg, "Projection");
    GLuint viewLocation = glGetUniformLocation(flatShaderPrg, "View");

    STP3D::IndexedMesh glMesh ( mesh );
    glMesh.createVAO();
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE );

     glViewport( 0, 0, width, height );
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_DEPTH_TEST);

        // Mouse states
        int leftButton = glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_LEFT );
        int rightButton = glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_RIGHT );
        int middleButton = glfwGetMouseButton( window, GLFW_MOUSE_BUTTON_MIDDLE );

        if( leftButton == GLFW_PRESS )
            guiStates.lock_turn();
        else
            guiStates.unlock_turn();

        if( rightButton == GLFW_PRESS )
            guiStates.lock_zoom();
        else
            guiStates.unlock_zoom();

        if( middleButton == GLFW_PRESS )
            guiStates.lock_pan();
        else
            guiStates.unlock_pan();

        // Camera movements
        int altPressed = glfwGetKey( window, GLFW_KEY_LEFT_SHIFT );
        if (!altPressed && (leftButton == GLFW_PRESS || rightButton == GLFW_PRESS || middleButton == GLFW_PRESS))
        {
            double x; double y;
            glfwGetCursorPos(window,&x, &y);
            guiStates.set_position_x( x );
            guiStates.set_position_y( y );
        }

        if (altPressed == GLFW_PRESS)
        {
            double mousex; double mousey;
            glfwGetCursorPos(window,&mousex, &mousey);
            double diffLockPositionX = mousex - guiStates.get_position_x();
            double diffLockPositionY = mousey - guiStates.get_position_y();
            if (guiStates.zoom())
            {
                float zoomDir = 0.0;
                if (diffLockPositionX > 0.)
                    zoomDir = -1.f;
                else if (diffLockPositionX < 0. )
                    zoomDir = 1.f;
                camera.zoom(zoomDir);
            }
            else if (guiStates.turn())
            {
                camera.turn(diffLockPositionY, diffLockPositionX);

            }
            else if (guiStates.pan())
            {
                camera.pan(diffLockPositionX, diffLockPositionY);
            }
            guiStates.set_position_x ( mousex );
            guiStates.set_position_y ( mousey );
        }


        /* Blender like background color */
        glClearColor ( 0.2235f, 0.2235f, 0.2235f, 0.0f );
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glUseProgram(flatShaderPrg);

        glm::mat4 projection = glm::perspective(45.0f, widthf / heightf, .1f, 100.f);
        glm::mat4 worldToView = glm::lookAt(camera.eye, camera.o, camera.up);


        // Upload uniforms
        glUniformMatrix4fv(projectionLocation, 1, 0, glm::value_ptr(projection));
        glUniformMatrix4fv(viewLocation, 1, 0, glm::value_ptr(worldToView));

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

