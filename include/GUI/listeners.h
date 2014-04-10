#ifndef LISTENERS_H
#define LISTENERS_H

#include <memory>
#include <vector>

class FlowRunnerListener
{
public:
    virtual void data_generated ( std::shared_ptr< Mesh > mesh, std::vector < float > * vectors ) = 0;
};

class GUIListener
{
public:
    virtual void time_changed (float time) = 0;
};

#endif // LISTENERS_H
