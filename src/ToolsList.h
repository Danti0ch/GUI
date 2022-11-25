#ifndef TOOLS_LIST_H
#define TOOLS_LIST_H

#include "ListWidget.h"
#include "ToolManager.h"

class ToolsList : public VListWidget<ToolManager>{
public:
    ToolsList(uint x, uint y, uint width, uint height);
    ~ToolsList();

    ToolManager* toolManager();
private:
    ToolManager manager_;
};

#endif // TOOLS_LIST_H
