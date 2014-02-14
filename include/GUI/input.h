/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  Kacper Pluta <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "statemonitor.h"

class Input
{
private:
    GUIStateMonitor guiStates;
    Input() {}
    void window_size_impl ( int width, int height )
    {
      glViewport( 0, 0, width, height );
    }
    
    void mouse_button_impl ( GLFWwindow * window, Camera & camera );
public:
    static Input & instance()
    {
        static Input _instance;
        return _instance;
    }

    static void window_size_callback ( GLFWwindow* window, int width, int height )
    {
      instance().window_size_impl ( width, height );
    }
    
    static void mouse ( GLFWwindow * window, Camera & camera ) 
    {
      instance().mouse_button_impl ( window, camera );
    }
};

#endif // INPUT_H
