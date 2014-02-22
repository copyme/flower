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
    _output = std::shared_ptr< Mesh > ( new Mesh );
    _output->set_model( _input->get_model() );

    //copy faces to output
    for ( unsigned int i = 0; i < _input->face_count(); i++ )
    {
        Face face = _input->get_face(i);
        for (unsigned int j = 0; j < face.model(); j++ )
            _output->add_face_vertex(face[j]);
    }
    _flow.output( _output.get() );
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
        (*it)->data_generated ( _output );
    }
}
