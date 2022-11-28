#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

#include "CanvasWidget.h"
#include "ListWidget.h"
#include "Label.h"

// TODO: save implementing

// TODO: maybe path ptr or widget without ptr, figure out
// TODO: rename
struct CanvasStorage{
    std::string path;
    CanvasWidget* widget;
};

class CanvasManager : public ContainerWidget{
public:
    CanvasManager(ToolManager* toolManager);
    ~CanvasManager();

    void setActive(uint n_canvas);
    void addCanvas(const std::string& path);
    void removeCanvas(const std::string& path);

    void draw() override;
private:
    HListWidget<CanvasManager> canvas_list_;
    std::list<CanvasStorage> storage_;
    Label default_text_;
    ToolManager* tool_manager_;
    
    CanvasWidget* active_canvas;
};

#endif // CANVAS_MANAGER_H
