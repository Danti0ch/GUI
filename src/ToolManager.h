#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "tools.hpp"
#include <list>
#include <string>
#include "Event.h"
#include "stImage.h"
struct ToolWrapper{
    booba::Tool* p;
    std::string name;
};

// TODO: rename
const char PLAGINS_FOLDER_PATH[] = "../bin/plugins";

class ToolManager{
public:
    static ToolManager* ACTIVE_TOOL_MANAGER;

    ToolManager();
    ~ToolManager();

    bool updateTools();
    void apply(stImage* space, const Event* event);

    // TODO: to const
    void addTool(booba::Tool* p_tool);
    //void setActiveTool(const booba::Tool* new_active_tool);
    void setActiveTool(uint n_tool);

    booba::Tool* getActiveTool();

    bool checkToolExists(const booba::Tool* tool);
    bool checkToolExists(const std::string& tool_name);

    const std::list<ToolWrapper>& tools() const;

private:
    std::list<ToolWrapper> tools_;
    booba::Tool* p_active_tool_;
};

#endif // TOOL_MANAGER_H
