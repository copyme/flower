/***************************************************************************
                        globals.hpp  -  description
                             -------------------
    copyright            : (C) 2012 by Biri
    email                : biri@univ-mlv.fr
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef _STP3D_GLOBALS_H
#define _STP3D_GLOBALS_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

/** \namespace STP3D
  * STP3D for Simple_Teaching_Platform_for_3D is a simple (and naive) C++ 3D library for 3D programming.
  * Inspired by GLM
  * Deals essentially with basic maths, basic image loading, basic shader and mesh handling, basic stufs.
  * \author Venceslas BIRI
  */
namespace STP3D {

#define STP3D_EPSILON 1e-6
#define GL_DEFINED

#ifdef GL_DEFINED

#include <GL/glew.h>
#include <GL/gl.h>

// ///////////////////////////////////////////////////////////////////////////
// GL check tool
// ///////////////////////////////////////////////////////////////////////////
inline void checkGL(int line, const char *filename) {
    int err = glGetError();
    if(err != GL_NO_ERROR) {
        std::cerr << "ERROR GL : erreur dans le fichier " << filename << " à la ligne " ;
        std::cerr << line << " : " << gluErrorString(err) << std::endl;
        exit(0);
    }
}
#define CHECK_GL STP3D::checkGL(__LINE__, __FILE__);

#endif // GL_DEFINED

// ///////////////////////////////////////////////////////////////////////////
// Error msg mechanism
// ///////////////////////////////////////////////////////////////////////////
static std::string errSTP3D_Msg = std::string("No Error");
inline bool errorOccured() {
    return (strcmp(errSTP3D_Msg.c_str(),"No Error")!=0);
}
inline std::string getError() {
    return errSTP3D_Msg;
}
inline void setError(std::string inputErrMsg) {
    errSTP3D_Msg = inputErrMsg;
}
inline void eraseError() {
    errSTP3D_Msg = std::string("No Error");
}


} // Namespace Ends

#endif // _STP3D_GLOBALS_H
