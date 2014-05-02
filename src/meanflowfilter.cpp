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
#include <cassert>
#include <iostream>
#include <cmath>
#include "meanflowfilter.h"
#include "point.h"

//! \todo remove
static inline float clamp ( float val, int precision )
{
  float prec = std::pow ( 10.f, precision - 1 );
  return std::floor ( val * prec ) / prec;
}
//! \todo remove
static inline float up ( float val, int precision )
{
  float prec = std::pow ( 10.f, precision - 1 );
  return std::ceil ( val * prec ) / prec;
}

static float cosine_similarity ( Vector < float > & v1, Vector < float > & v2 )
{
    float angle = std::acos ( v1.dot( v2 ) / ( v1.length() * v2.length() ) );
    if ( std::isnan ( angle ) )
      angle = 0.f;
    return angle;
}

void MeanFlowFilter::execute()
{
    assert ( mesh_in != NULL );
    assert ( mesh_out != NULL );

    for ( unsigned int i = 0; i < mesh_in->vertex_count(); i++ )
    {
        Vector < float > vector;
	try 
	{
	  vector = calculate_vector ( i );
	}
	catch ( std::runtime_error )
	{
	  vector = calculate_boundary_vector ( i );
	}
	
        Point < float > point ( mesh_in->get_vertex ( i ) );
	if ( vectors != nullptr )
	{
	  vectors->push_back(point[0]);
	  vectors->push_back(point[1]);
	  vectors->push_back(point[2]);
	}
	point += vector;
        mesh_out->add_vertexs_coord ( point[0] );
        mesh_out->add_vertexs_coord ( point[1] );
        mesh_out->add_vertexs_coord ( point[2] );
	
	if ( vectors != nullptr )
	{
	  vectors->push_back(point[0]);
	  vectors->push_back(point[1]);
	  vectors->push_back(point[2]);
	}
    }
}

Vector < float > MeanFlowFilter::calculate_vector( unsigned int point )
{
  Vector < float > vector;
  
  std::pair< Mesh::StarConstIter, Mesh::StarConstIter > range = mesh_in->get_start ( point );
  
  Mesh::StarConstIter it = range.first;
  Mesh::StarConstIter end = range.second;
  
  for ( ; it != end; ++it )
  {
    if ( it->second.get_faces().first == -1 ||  it->second.get_faces().second == -1 )
      throw std::runtime_error ( "Boundary edge detected!" );
    
    Vector < float > N1 = mesh_in->get_normal( it->second.get_faces().first );
    Vector < float > N2 = mesh_in->get_normal( it->second.get_faces().second );
    float theta = cosine_similarity ( N1, N2 );
    Vector < float > N_E = ( N1 + N2 ) / ( 2.f * std::cos ( theta / 2.f ) );
    
    Vertex end = mesh_in->get_vertex ( point );
    Vertex start = mesh_in->get_vertex ( it->second.end() );
    Vector < float > tmpVector ( start, end );
    N_E *= tmpVector.length() * std::sin( theta / 2.f );
    vector += N_E;
  }
  vector *= -0.5f;
  vector *= step;
  return vector;
}

Vector < float > MeanFlowFilter::calculate_boundary_vector ( unsigned int point )
{
  std::pair< Mesh::StarConstIter, Mesh::StarConstIter > range = mesh_in->get_start ( point );
  
  Mesh::StarConstIter it = range.first;
  Mesh::StarConstIter end = range.second;
  
  Vector < float > q1p ( mesh_in->get_vertex ( point ), mesh_in->get_vertex ( it->second.end() ) );
  float phi_2 = calculate_phi_minus ( it->second, std::next ( it )->second );
  q1p *= ( 1.f / std::tan ( phi_2 ) ) / 2.f;
  Vector < float > vector;
  
  if ( std::distance ( it, end ) > 2 )
  {
    int i;
    for ( ++it, --end; it != end; ++it )
    {
      float sum = 0;
      sum += 1.f / std::tan ( calculate_phi_minus ( it->second, std::next ( it ) ->second ) );
      sum += 1.f / std::tan ( calculate_phi_plus ( std::prev ( it ) ->second, it->second ) );
      Vector < float > qip ( mesh_in->get_vertex ( point ), mesh_in->get_vertex ( it->second.end() ) );
      qip *= sum;
      vector += qip;
    }
    vector *= 0.5f;
  }
  
  vector += q1p;
  
  float phi_n = calculate_phi_plus ( std::prev ( range.second, 2 )->second, std::prev ( range.second )->second  );
  Vector < float > qnp ( mesh_in->get_vertex ( point ), mesh_in->get_vertex ( std::prev ( range.second , 1 )->second.end() ) );
  qnp *= ( 1.f / std::tan ( phi_n ) ) / 2.f;
  vector += qnp;
  vector *= step;
  
  return vector;
}

float MeanFlowFilter::calculate_phi_minus ( Edge const & e1, Edge const & e2 )
{
  Vector < float > v1 ( mesh_in->get_vertex( e2.end() ), mesh_in->get_vertex ( e2.begin() ) ); 
  Vector < float > v2 ( mesh_in->get_vertex( e2.end() ), mesh_in->get_vertex ( e1.end() ) );
  
  return cosine_similarity ( v1, v2 );
}

float MeanFlowFilter::calculate_phi_plus ( Edge const & e1, Edge const & e2 )
{
  Vector < float > v1 ( mesh_in->get_vertex( e1.end() ), mesh_in->get_vertex ( e1.begin() ) ); 
  Vector < float > v2 ( mesh_in->get_vertex( e1.end() ), mesh_in->get_vertex ( e2.end() ) );
  
  return cosine_similarity ( v1, v2 );
}
