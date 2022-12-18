#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

#include "CanvasWidget.h"
#include "ListWidget.h"
#include "Label.h"
#include "optionals.hpp"
#include "EventWrapper.h"

// TODO: rewrite on barwidget
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
    void addCanvas(std::string path);
    void removeCanvas(const std::string& path);

    static CanvasWidget* ACTIVE_CANVAS_WIDGET;
    static CanvasManager* ACTIVE_CANVAS_MANAGER;

    void draw() override;

    DrawableArea* hiddenLayer();
private:
    HListWidget*             canvas_list_;
    std::list<CanvasStorage> storage_;
    Label*                   default_text_;
    ToolManager*             tool_manager_;
    
    DrawableArea*            hiddenLayer_;
    CanvasWidget*            active_canvas;
};

#endif // CANVAS_MANAGER_H
