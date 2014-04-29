/*=========================================================================
  
  Program:   
  Module:    <>
  
  Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
  All rights reserved.
  See Copyright.txt for details.
  
     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.
     
=========================================================================*/

#ifndef POWERMEANCURVATUREFLOWFILTER_H
#define POWERMEANCURVATUREFLOWFILTER_H

#include "meanflowfilter.h"

class PowerMeanFlowFilter : public MeanFlowFilter
{
private:
  float POWER;
protected:
    virtual Vector < float > calculate_vector ( unsigned int point );
    virtual Vector < float > calculate_boundary_vector ( unsigned int point );
public:
  PowerMeanFlowFilter ( float power );
};



#endif // POWERMEANCURVATUREFLOWFILTER_H
