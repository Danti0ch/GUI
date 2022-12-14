#ifndef TOOL_MANAGER_H
#define TOOL_MANAGER_H

#include "tools.hpp"
#include <list>
#include <string>
#include "Event.h"
#include "StatusBar.h"
#include "Expended.h"

struct ToolWrapper{
    booba::Tool* p;
    std::string name;
};

const uint TOOL_INACTIVE_IND = -1;
class CanvasWidget;
// TODO: rename
const char PLAGINS_FOLDER_PATH[] = "../bin/plugins";

class ToolManager{
public:
    // TODO: unsafe
    static ToolManager* ACTIVE_TOOL_MANAGER;
    
    ToolManager();
    ~ToolManager() = default;

    bool updateTools();
    void apply(CanvasWidget* space, const Event* event);
    void setupSliderMoved(const Slider* pSlider);

    void addTool(booba::Tool* p_tool);
    //void setActiveTool(const booba::Tool* new_active_tool);
    void setActiveTool(uint n_tool);

    booba::Tool* getActiveTool();
    uint getNActiveTool();

    bool checkToolExists(const booba::Tool* tool);
    bool checkToolExists(const std::string& tool_name);

    const std::list<ToolWrapper>& tools() const;

    void linkStatusBar(StatusBar* status_bar);
private:
    std::list<ToolWrapper> tools_;
    uint n_active_tool_;
    booba::Tool* p_active_tool_;
    
    StatusBar* p_status_bar_;
};

#endif // TOOL_MANAGER_H
