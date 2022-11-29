#ifndef SETUP_WIDGET_H
#define SETUP_WIDGET_H

#include "ExpendedContainerWidget.h"
#include "ToolManager.h"

class SetupWidget : public ExpendedContainerWidget{
public:
    SetupWidget(ToolManager* tool_manager);

    void onMouseLClick(const MouseLClickEvent* event) override;
    void onKeyPressed( const KeyPressedEvent* event) override;
    void onMouseReleased(const MouseReleasedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
    
    void onSliderMoved( const SliderMovedEvent* event) override;

private:
    ToolManager* tool_manager_;
};

#endif // SETUP_WIDGET_H
