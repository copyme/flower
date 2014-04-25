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

template <class T>
static inline int signum ( T n )
{
  return n > 0 ? 1 : -1;
}

PowerMeanFlowFilter::PowerMeanFlowFilter( int power ) : MeanFlowFilter()
{
  POWER = power;
}

Vector<float> PowerMeanFlowFilter::calculate_vector( unsigned int point )
{
  Vector<float> vector = MeanFlowFilter::calculate_vector ( point );
  
  if ( ( POWER  % 2 ) == 0 )
  {
    vector[0] = signum < float > ( vector[0] ) * std::pow ( vector[0], POWER );
    vector[1] = signum < float > ( vector[1] ) * std::pow ( vector[1], POWER );
    vector[2] = signum < float > ( vector[2] ) * std::pow ( vector[2], POWER );
  }
  else
  {
    vector[0] = std::pow ( vector[0], POWER );
    vector[1] = std::pow ( vector[1], POWER );
    vector[2] = std::pow ( vector[2], POWER );
  }
  
  return vector;
}

Vector < float > PowerMeanFlowFilter::calculate_boundary_vector ( unsigned int point )
{
  Vector<float> vector = MeanFlowFilter::calculate_boundary_vector ( point );
  
  if ( ( POWER  % 2 ) == 0 )
  {
    vector[0] = signum < float > ( vector[0] ) * std::pow ( vector[0], POWER );
    vector[1] = signum < float > ( vector[1] ) * std::pow ( vector[1], POWER );
    vector[2] = signum < float > ( vector[2] ) * std::pow ( vector[2], POWER );
  }
  else
  {
    vector[0] = std::pow ( vector[0], POWER );
    vector[1] = std::pow ( vector[1], POWER );
    vector[2] = std::pow ( vector[2], POWER );
  }
  return vector;
}
