#ifndef SETUP_WIDGET_H
#define SETUP_WIDGET_H

#include "Expended.h"
#include "ToolManager.h"

class SetupWidget : public Expended{
public:
    SetupWidget(ToolManager* tool_manager);
    ~SetupWidget();

    static SetupWidget* ACTIVE_SETUP_WINDOW;

    void onMouseButtonPressed(const MouseButtonPressedEvent* event);
    void onMouseButtonReleased(const MouseButtonReleasedEvent* event);
    void onMouseMoved(const MouseMovedEvent* event);
    void onKeyPressed( const KeyPressedEvent* event);
    void onKeyReleased( const KeyReleasedEvent* event);

    void addSetupWidget(Widget* widget, Vector pos);
private:
    ToolManager* tool_manager_;
    std::vector<Widget*> setupWindowWidgets_;
};

#endif // SETUP_WIDGET_H
