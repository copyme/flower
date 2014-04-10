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
#include "glines.h"

#define OPENGL_MAJOR_VERSION 3
#define OPENGL_MINOR_VERSION 0 //! Obligatory thus we use GL_QUADS

class Interface : public FlowRunnerListener
{
private:
    static const char * shaderFileVer;
    static const char * shaderFileFrag;
    GLuint projectionLocation;
    GLuint viewLocation;
    GLuint color;
    GLuint shaderProgram;
    bool show_vectors;
    GLFWwindow * window;
    GLFWvidmode const * screen;
    Camera camera;
    STP3D::IndexedMesh glMesh;
    GLines gLines;
    std::shared_ptr< Mesh > mesh;
    GUIStateMonitor guiStates;
    std::vector < float > * vectors;
    std::list < GUIListener * > listeners;
    void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
public:
    virtual void data_generated ( std::shared_ptr< Mesh > mesh, std::vector < float > * vectors  );
    Interface();
    void register_listener ( GUIListener * listener );
    void remove_listener ( GUIListener * listener );
    void init( Mesh & mesh );
    int exec ();
};

#endif // INTERFACE_H
