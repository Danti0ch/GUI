#include "ToolsList.h"

//? should i make version that non-depended on class type?

ToolsList::ToolsList(uint x, uint y, uint width, uint height):
    manager_(),
    VListWidget<ToolManager>(x, y, width, height, 30, &manager_, &ToolManager::setActiveTool)
{
    manager_.updateTools();

    const std::list<ToolWrapper> tools = manager_.tools();
    std::list<ToolWrapper>::const_iterator tools_iter;
    
    for (tools_iter = tools.begin(); tools_iter != tools.end(); tools_iter++){
        add(tools_iter->name);
    }
}

ToolsList::~ToolsList(){}

ToolManager* ToolsList::toolManager(){
    return &manager_;
}
