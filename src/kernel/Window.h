#ifndef WINDOW_H
#define WINDOW_H

#include "Widget.h"
#include "ListWidget.h"

/**
 * @brief widget representing window the window at the display
 * 
 */
class Window : public ContainerWidget{
public:
    Window(Vector size);
    ~Window();

    void add(Widget* widget, Vector pos);
    void remove(Widget* widget);
    
    void exec();
    virtual void onMouseButtonPressed(const MouseButtonPressedEvent* event);

private:
    void drawContextMenu(Vector pos, VListWidget* menu);

//private:
//    void updateManipulatorsData(Event* event);
private:
    RealWindow* realWindow_;
    VListWidget* activeContextMenu_;
    EventManager* eventManager_;

friend class Widget;
friend class ContainerWidget;

// TODO: fix

friend class Contexted;
};

#endif // WINDOW_H
