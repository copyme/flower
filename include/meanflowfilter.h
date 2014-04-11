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
#include "flowfilter.h"
#include "Vector.h"
#include <vector>


/** \brief Implementation of mean curvature flow
 * \todo change assertions to exceptions
 */
class MeanFlowFilter : public FlowFilter
{
private:
    Mesh const * mesh_in;
    Mesh * mesh_out;
    std::vector < float > * vectors;
    float step;
    Vector < float > calculate_vector ( unsigned int point );
public:
    MeanFlowFilter () {
        step = 0.;
	vectors = nullptr;
    }
    void input ( Mesh const * mesh ) {
        this->mesh_in = mesh;
    }
    Mesh const * get_input () const {
        return mesh_in;
    }
    void output ( Mesh * mesh ) {
        this->mesh_out = mesh;
    }
    inline float get_time () const {
        return step;
    }
    inline void set_time (float value) {
        step = value;
    }
    void set_debug( std::vector < float > * vectors ) { this->vectors = vectors;  };
    void execute();
};

#endif // MEANFLOWFILTER_H
