/*=========================================================================
 *
 * Program:
 * Module:    <>
 *
 * Copyright (c) Kacper Pluta <kacper.pluta@dbslabs.com.br>
 *               Meri-nut Zago <meri_zago@hotmail.fr>
 * All rights reserved.
 * See Copyright.txt for details.
 *
 *    This software is distributed WITHOUT ANY WARRANTY; without even
 *    the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *    PURPOSE.  See the above copyright notice for more information.
 *
 = *========================================================================*/
#include <algorithm>
#include <thread>
#include "flowrunner.h"


FlowRunner::FlowRunner ( FlowFilter & flow ): _flow ( flow ) {
    runnning = false;
    _input = _flow.get_input();
    _flow.set_debug ( &vectors );
    _output.copy_faces(_input);
    _output.set_model( _input->get_model() );
}

void FlowRunner::register_listener ( FlowRunnerListener * listener )
{
    if ( std::find ( listeners.begin(), listeners.end(), listener ) == listeners.end() )
    {
        listeners.push_back ( listener );
    }
}

void FlowRunner::remove_listener ( FlowRunnerListener * listener )
{
    listeners.remove ( listener );
}


void FlowRunner::time_changed ( float time )
{
  if ( runnning )
    return;
  runnning = true;
  _flow.set_time ( time );
  
  std::thread _thred = std::thread ( &FlowRunner::run, this );
  _thred.detach();
}

void FlowRunner::run ()
{    
  vectors.clear();
  _output.clear_vertices();
  _flow.set_output ( &_output );
  _flow.execute();
  emit();
  runnning = false;
}

void FlowRunner::emit ()
{
    std::list < FlowRunnerListener * >::iterator it = listeners.begin();
    std::list < FlowRunnerListener * >::const_iterator end = listeners.cend();
    for (; it != end; ++it )
    {
        (*it)->data_generated ( &_output, &vectors );
    }
}
