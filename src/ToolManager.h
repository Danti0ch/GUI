#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "tools.hpp"
#include <list>
#include <string>
#include "Event.h"

struct ToolWrapper{
    booba::Tool* p;
    std::string name;
};

const char PLAGINS_FOLDER_PATH[] = "plugins/";

class ToolManager{
public:
    ToolManager();
    ~ToolManager();

    void updateTools();
    void apply(Event* event);

    void setActiveTool(booba::Tool* new_active_tool);
    Tool* getActiveTool();

    bool checkToolExists(const Tool* tool);
    bool checkToolExists(const std::string& tool_name);
    
private:
    std::list<ToolWrapper> tools_;
    booba::Tool* p_active_tool_;
};

#endif // TOOL_MANAGER_H
