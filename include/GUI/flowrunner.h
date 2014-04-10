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

#ifndef FLOWRUNNER_H
#define FLOWRUNNER_H

#include <list>
#include <memory>
#include "mesh.h"
#include "listeners.h"
#include "meanflowfilter.h"

class FlowRunner : public GUIListener
{
private:
    std::shared_ptr< Mesh > _output;
    std::vector < float > vectors;
    Mesh const * _input;
    bool runnning;
    std::list < FlowRunnerListener * > listeners;
    FlowFilter & _flow;
    void run ();
    void emit();
public:
    FlowRunner ( FlowFilter & flow );
    virtual void time_changed ( float time );
    void register_listener ( FlowRunnerListener * listener );
    void remove_listener ( FlowRunnerListener * listener );
};

#endif // FLOWRUNNER_H
