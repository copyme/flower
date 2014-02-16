#ifndef LISTENERS_H
#define LISTENERS_H

class FlowRunnerListener
{
public:
    virtual void data_generated ( Mesh * mesh ) = 0;
};

class GUIListener
{
public:
    virtual void time_changed (float time) = 0;
};

#endif // LISTENERS_H