#ifndef WINDOW_H
#define WINDOW_H

#include "Widget.h"
#include <iostream>
class Window : public ContainerWidget{
public:
    Window(uint width, uint height);

    void add(Widget* widget);
    void remove(Widget* widget);
    
    void exec();
private:
    GraphicSpace space_;
    EventManager manager_;
};

#endif // WINDOW_H
