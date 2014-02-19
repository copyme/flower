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

#include "input.h"

void Input::mouse_button_impl ( GLFWwindow * window, Camera & camera )
{
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
}