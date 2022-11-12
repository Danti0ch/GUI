#ifndef WINDOW_H
#define WINDOW_H

#include "Widget.h"
#include "EventManager.h"
#include <iostream>
class Window : public ContainerWidget{
public:
    Window(uint width, uint height);

    void exec();
private:
    GraphicSpace space_;
    EventManager manager_;
    PixelBuffer  pix_buf_;
};

#endif // WINDOW_H
