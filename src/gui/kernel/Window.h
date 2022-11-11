#ifndef WINDOW_H
#define WINDOW_H

#include "ContainerWidget.h"
#include "EventManager.h"
#include <iostream>
class Window : public ContainerWidget{
public:
    Window(uint width, uint height);

    void exec();
private:
    GraphicSpace space_;
    EventManager manager_;
};

#endif // WINDOW_H
