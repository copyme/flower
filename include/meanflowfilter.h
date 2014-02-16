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

class FlowFilter
{
public:
    virtual void input ( Mesh const * mesh ) = 0;
    virtual Mesh const * get_input () const = 0; 
    virtual void output ( Mesh * mesh ) = 0;
    virtual float get_step() const = 0;
    virtual void set_step ( float value) = 0;
    virtual void execute() = 0;
};


class MeanFlowFilter : public FlowFilter
{
private:
    Mesh const * mesh_in;
    Mesh * mesh_out;
    float step;
    Vector < double > calculate_vector (const std::vector<Edge> &edges, unsigned int point );
public:
    MeanFlowFilter () { step = 0.; }
    void input ( Mesh const * mesh ) { this->mesh_in = mesh; }
    Mesh const * get_input () const { return mesh_in; }
    void output ( Mesh * mesh ) { this->mesh_out = mesh; }
    inline float get_step () const { return step; }
    inline void set_step (float value) { step = value; }
    void execute();
};

#endif // MEANFLOWFILTER_H
