#include "ToolsList.h"

//? should i make version that non-depended on class type?

ToolsList::ToolsList():
    manager_(),
    VListWidget<ToolManager>(150, 560, 30, &manager_, &ToolManager::setActiveTool)
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
