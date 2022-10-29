#include "Window.h"

Window::Window(uint width, uint height):
    ContainerWidget(0, 0, width, height),
    space(width, height),
    pix_buf_(width, height)
{}
