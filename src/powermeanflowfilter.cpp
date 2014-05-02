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

#include <cmath>
#include "powermeanflowfilter.h"

PowerMeanFlowFilter::PowerMeanFlowFilter( float power ) : MeanFlowFilter()
{
  POWER = power;
}

Vector<float> PowerMeanFlowFilter::calculate_vector( unsigned int point )
{
  Vector < float > vector = MeanFlowFilter::calculate_vector ( point );
  vector *= std::pow ( vector.length(), POWER - 1 );
  if ( !std::isnan ( vector.length() ) )
    return vector;
  else
    return Vector < float >();
}

Vector < float > PowerMeanFlowFilter::calculate_boundary_vector ( unsigned int point )
{
  Vector < float > vector = MeanFlowFilter::calculate_boundary_vector ( point );
  vector *= std::pow ( vector.length(), POWER - 1 );
  if ( !std::isnan ( vector.length() ) )
    return vector;
  else
    return Vector < float >();
}
