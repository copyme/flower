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

#include <cstring>
// #include <string>
#include <iostream>
#include <stdexcept>
#include "flowfactory.h"
// #include <CSVExtractor.h>
#include "meanflowfilter.h"
#include "powermeanflowfilter.h"

std::shared_ptr< FlowFilter > FlowFactory::get_flow ( const char * name, const char * params )
{
  if ( strcmp ( "MEAN", name ) == 0 )
  {
    return std::shared_ptr< FlowFilter > ( new MeanFlowFilter() );
  }
  else if ( strcmp ( "POWER_MEAN", name ) == 0 )
  {
    if ( strcmp ( "null", params ) != 0 )
    {
      /* 
       * You can use CSVExtractor to easily get values from comma separated string.
       * CSVExtractor extractor;
       * extractor.input(std::string( params) );
       * int param = std::atoi ( extractor.getValue ( 0 ).c_str() );
      */
      float param = std::atof ( params );
      return std::shared_ptr< FlowFilter > ( new PowerMeanFlowFilter( param ) );
    }
    else
    {
      std::cerr << "Warrning: PowerMeanFlowFilter created with standard power - 2." << std::endl;
      return std::shared_ptr< FlowFilter > (  new PowerMeanFlowFilter( 2.f ) );
    }
  }
  else
    throw std::runtime_error ( "FlowFactory: Non registered flow!" );
}