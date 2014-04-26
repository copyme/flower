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

#include <iostream>

#include <cassert>
#include <cstddef>
#include <algorithm>
#include "edgeextractor.h"

EdgeExtractor::EdgeExtractor()
{
    mesh = NULL;
}

void EdgeExtractor::init ( const Mesh *mesh )
{
    assert ( mesh != NULL );
    this->mesh = mesh;
}

static void insert_once ( std::vector < Edge > & edges, Edge & t_edge )
{
  std::vector < Edge >::iterator it = std::find(edges.begin(), edges.end(), t_edge );
  if( it == edges.end() )
    edges.push_back ( t_edge );
}

void EdgeExtractor::init_faces( Edge & t_edge, unsigned int i )
{
    t_edge.add_face ( i );
    std::vector < Edge >::iterator it = std::find(edges.begin(), edges.end(), t_edge );
    if( it == edges.end() )
        return;
    t_edge.add_face ( it->get_faces().first );
    it->add_face( i );
}

void EdgeExtractor::extract ( unsigned int index )
{
    assert ( mesh != NULL );
    edges.clear();
    for ( unsigned int i = 0; i < mesh->face_count(); i++ )
    {
        Face const face = mesh->get_face ( i );
        for ( unsigned int j = 0; j < face.model(); j++ )
        {
            if ( face[j] == index )
            {
                //middle - right
                if ( j + 1 <  face.model() )
                {
                    Edge t_edge( face.begin() + j, face.begin() + j + 1 );
                    init_faces(t_edge, i);
		    insert_once ( edges, t_edge );
                }
                //beginning
                if ( j ==  0 )
		{
		  Edge t_edge( face.begin(), face.end() - 1 );
		  init_faces(t_edge, i);
		  insert_once ( edges, t_edge );
		}
                //middle - left
                if ( j > 0 )
                {
                    Edge t_edge ( face.begin()+j, face.begin() + j - 1 );
                    init_faces(t_edge, i);
		    insert_once ( edges, t_edge );
                }
                //end
                if ( j == face.model() - 1 )
                {
                    Edge t_edge( face.begin() + j, face.begin() );
                    init_faces(t_edge, i);
		    insert_once ( edges, t_edge );
                }
            }
        }
    }
    int check_point = check();
    if ( check_point != -1 )
      fix_boundary_case_order ( check_point );
}

int EdgeExtractor::check()
{
  for (int i = 0; i < edges.size(); i++)
  {
    if ( edges.at(i).get_faces().second == -1 )
      return i;
  }
  return -1;
}

void EdgeExtractor::fix_boundary_case_order ( int start_index )
{
  std::swap( edges[start_index], edges[0] );
  
  for ( int i = 0; i < edges.size() - 1; i++ )
  {
    for ( int j = i + 1; j < edges.size(); j++ )
    {
      if ( edges.at(i).get_faces().first == edges.at(j).get_faces().first || edges.at(i).get_faces().first == edges.at(j).get_faces().second )
      {
	std::swap( edges[i+1], edges[j] );
	break;
      }
      else if ( ( edges.at(i).get_faces().second == edges.at(j).get_faces().first || edges.at(i).get_faces().second == edges.at(j).get_faces().second )
	&& (edges.at(i).get_faces().second != -1) )
      {
	std::swap( edges[i+1], edges[j] );
	break;
      }
    }
  }
}