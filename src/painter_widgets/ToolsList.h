#ifndef TOOLS_LIST_H
#define TOOLS_LIST_H

#include "ListWidget.h"
#include "ToolManager.h"
#include "SetupWidget.h"
#include "Textured.h"

class ToolsList : public ContainerWidget{
public:
    ToolsList();
    ~ToolsList();

    ToolManager* toolManager();

    void ScrolledSlot(double ratio);

private:
    VListWidget* list_;
    ToolManager* manager_;
    std::list<SetupWidget*> setupWidgets_;
private:
    void setActiveTool(uint n_tool);
};

#endif // TOOLS_LIST_H
