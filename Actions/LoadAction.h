#pragma once
#include "Action.h"
class LoadAction :
    public Action
{
    string File_Name;
    bool invalid;
public:
    LoadAction(ApplicationManager* pAppManager);
    void ReadActionParameters();
    void Execute();

};
