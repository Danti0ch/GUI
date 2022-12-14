#ifndef CANVAS_WIDGET_H
#define CANVAS_WIDGET_H

#include "tools.hpp"
#include "Expended.h"
#include "ToolManager.h"

class CanvasWidget : public Expended{
public:

    CanvasWidget(Vector size, ToolManager* tool_manager);
    ~CanvasWidget();

    // TODO: OTHER HANDLERS
    void onMouseButtonPressed(const MouseButtonPressedEvent* event);
    void onMouseButtonReleased(const MouseButtonReleasedEvent* event);
    void onMouseMoved(const MouseMovedEvent* event);

    void draw() override;

    DrawableArea* drawableLayer();

private:
    ToolManager* tool_manager_;
    DrawableArea* drawableLayer_;

private:

    //?
    //void connectDataUpdate_(Widget* container);
    //void disconnectDataUpdate_();
};

#endif // CANVAS_WIDGET_H
