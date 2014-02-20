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

#ifndef MEANFLOWFILTER_H
#define MEANFLOWFILTER_H

#include "mesh.h"
#include "Vector.h"
#include <vector>

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
    virtual void output ( Mesh * mesh ) = 0;
    virtual float get_time() const = 0;
    virtual void set_time ( float value ) = 0;
    //! Implementation should throw exception if one of meshes wes not set.
    virtual void execute() = 0;
};

/** \brief Implementation of mean curvature flow
 * \todo change assertions to exceptions
 */
class MeanFlowFilter : public FlowFilter
{
private:
    Mesh const * mesh_in;
    Mesh * mesh_out;
    float step;
    Vector < float > calculate_vector (const std::vector<Edge> &edges, unsigned int point );
public:
    MeanFlowFilter () { step = 0.; }
    void input ( Mesh const * mesh ) { this->mesh_in = mesh; }
    Mesh const * get_input () const { return mesh_in; }
    void output ( Mesh * mesh ) { this->mesh_out = mesh; }
    inline float get_time () const { return step; }
    inline void set_time (float value) { step = value; }
    void execute();
};

#endif // MEANFLOWFILTER_H
