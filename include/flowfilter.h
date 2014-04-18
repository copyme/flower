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

#ifndef FLOWFILTER_H
#define FLOWFILTER_H

#include "mesh.h"

/** \brief This abstract class is an interface for classes which implement flows.
 * \todo move to another file.
 */
class FlowFilter
{
public:
    //! \param mesh which will be under flow. This mesh will be unchanged
    virtual void input ( Mesh const * mesh ) = 0;
    virtual Mesh const * get_input () const = 0;
    //! \param mesh where filter will store new mesh parameters after flowing
    virtual void set_output ( Mesh * mesh ) = 0;
    virtual float get_time() const = 0;
    virtual void set_time ( float value ) = 0;
    //! Implementation should throw exception if at least one of meshes is not set.
    virtual void execute() = 0;
    //! For access to curvature vectors of vertices
    virtual void set_debug( std::vector < float > * vectors ) = 0;
};

#endif // FLOWFILTER_H