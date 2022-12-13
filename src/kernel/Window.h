#ifndef WINDOW_H
#define WINDOW_H

#include "Widget.h"

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
private:
    void updateManipulatorsData(Event* event);
private:
    RealWindow* window_;
};

#endif // WINDOW_H
