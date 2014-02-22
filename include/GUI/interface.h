/*=========================================================================

  Program:
  Module:    <>

  Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
                Meri-nut Zago <meri_zago@hotmail.fr>
  All rights reserved.
  See Copyright.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <memory>
#include <list>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "statemonitor.h"
#include "indexed_mesh.hpp"
#include "camera.h"
#include <mesh.h>
#include "listeners.h"


class Interface : public FlowRunnerListener
{
private:
    static const char * shaderFileVer;
    static const char * shaderFileFrag;
    GLuint projectionLocation;
    GLuint viewLocation;
    GLuint color;
    GLuint shaderProgram;
    GLFWwindow * window;
    GLFWvidmode const * screen;
    Camera camera;
    std::shared_ptr < STP3D::IndexedMesh > glMesh;
    GUIStateMonitor guiStates;
    std::list < GUIListener * > listeners;
    void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
public:
    virtual void data_generated ( std::shared_ptr< Mesh > mesh );
    Interface();
    void register_listener ( GUIListener * listener );
    void remove_listener ( GUIListener * listener );
    void init( Mesh & mesh );
    int exec ();
};

#endif // INTERFACE_H
