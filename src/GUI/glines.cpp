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

#include "glines.h"
#include <stdexcept>

GLines::GLines()
{
  vai = vbo = 0; 
}

void GLines::init()
{
  glGenVertexArrays(1, &vai);
  glGenBuffers(1, &vbo);
  
  if ( vai == 0 || vbo == 0 )
    throw std::runtime_error ( "Init of GLines faild!" );
}

void GLines::set_data( std::vector < float > * vectors )
{
  glBindVertexArray(vai);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof( float ) * vectors->size(), &(*vectors)[0], GL_STATIC_DRAW);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  size = vectors->size();
}
void GLines::draw()
{
  if(size == 0 || vai == 0 || vbo == 0)
    return;
  glBindVertexArray(vai);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
  glDrawArrays(GL_LINES, 0, size);
  glDisableVertexAttribArray(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}