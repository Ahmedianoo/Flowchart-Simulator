#pragma once
#include "Action.h"
class SaveAction :
    public Action
{
    string file_name;
public:
    SaveAction(ApplicationManager* pAppManager);
    virtual void ReadActionParameters();
    virtual void  Execute();
};
