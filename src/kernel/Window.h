#ifndef WINDOW_H
#define WINDOW_H

#include "Widget.h"
#include <iostream>
class Window : public ContainerWidget{
public:
    Window(uint width, uint height);

    void add(Widget* widget, uint x, uint y);
    void add(Widget* widget, Widget* from_widget, LINKAGE_MODE mode, uint indent_val = 0, uint offset = 0);
    void remove(Widget* widget);
    
    void exec();
private:
    GraphicSpace space_;
    EventManager manager_;
};

#endif // WINDOW_H
