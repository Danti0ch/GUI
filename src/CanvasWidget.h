#ifndef CANVAS_WIDGET_H
#define CANVAS_WIDGET_H

#include "tools.hpp"

#include "ExpendedContainerWidget.h"
#include "ToolManager.h"

class CanvasWidget : public ExpendedContainerWidget{
public:
    CanvasWidget(uint x, uint y, uint width, uint height, ToolManager* tool_manager);
    ~CanvasWidget();

    void onMouseLClick(const MouseLClickEvent* event) override;
    void onMouseReleased(const MouseReleasedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
private:
    ToolManager* tool_manager_;
    Color bg_color_;
    Color fg_color_;
};

#endif // CANVAS_WIDGET_H
