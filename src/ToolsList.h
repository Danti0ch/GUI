#ifndef TOOLS_LIST_H
#define TOOLS_LIST_H

#include "ListWidget.h"
#include "ToolManager.h"
#include "SetupWidget.h"

class ToolsList : public ContainerWidget{
public:
    ToolsList();
    ~ToolsList();

    ToolManager* toolManager();

    void onSliderMoved(const SliderMovedEvent* event) override;
private:
    VListWidget<ToolsList> list_;
    ToolManager manager_;
    std::list<SetupWidget*> setupWidgets_;
private:
    void setActiveTool(uint n_tool);
    void draw() override;
};

#endif // TOOLS_LIST_H
