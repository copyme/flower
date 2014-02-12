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

class MeanFlowFilter
{
private:
    Mesh const * mesh_in;
    Mesh * mesh_out;
    double step;
    Vector < double > calculate_vector (const std::vector<Edge> &edges, unsigned int point );
public:
    MeanFlowFilter () { step = 0.; }
    void input ( Mesh const * mesh ) { this->mesh_in = mesh; }
    void output ( Mesh * mesh ) { this->mesh_out = mesh; }
    void execute();
    inline double get_step() const { return step; }
    inline void set_step(double value) { step = value; }
};

#endif // MEANFLOWFILTER_H
