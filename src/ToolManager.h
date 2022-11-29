#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "tools.hpp"
#include <list>
#include <string>
#include "Event.h"
#include "StatusBar.h"
#include "ExpendedContainerWidget.h"

struct ToolWrapper{
    booba::Tool* p;
    std::string name;
};

const uint TOOL_INACTIVE_IND = -1;

// TODO: rename
const char PLAGINS_FOLDER_PATH[] = "../bin/plugins";

class ToolManager{
public:
    // TODO: unsafe
    static ToolManager* ACTIVE_TOOL_MANAGER;
    static ExpendedContainerWidget* ACTIVE_SETUP_WINDOW;
    
    ToolManager();
    ~ToolManager();

    bool updateTools();
    void apply(stImage* space, const Event* event);

    // TODO: to const
    void addTool(booba::Tool* p_tool);
    //void setActiveTool(const booba::Tool* new_active_tool);
    void setActiveTool(uint n_tool);

    booba::Tool* getActiveTool();
    uint getNActiveTool();

    bool checkToolExists(const booba::Tool* tool);
    bool checkToolExists(const std::string& tool_name);

    const std::list<ToolWrapper>& tools() const;

    void linkStatusBar(StatusBar* status_bar);

    void addSetupWidget(Widget* setup_widget);
private:
    std::list<ToolWrapper> tools_;
    uint n_active_tool_;
    booba::Tool* p_active_tool_;
    
    StatusBar* p_status_bar_;

    std::vector<Widget*> setupWindowWidgets_;
};

#endif // TOOL_MANAGER_H
