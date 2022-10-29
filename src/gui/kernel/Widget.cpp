#include "Widget.h"

// TODO: добавить возможность дефолтного конструктора где параметры расположения будут подбираться автоматически?
Widget::Widget(uint x, uint y, uint width, uint height):
    x_(x), y_(y), width_(width), height_(height),
    is_focused_(false),
    is_visible_(true),
    texture_()
{}

Widget::~Widget(){}

void coreDraw(LocPixBuffer* buf){
    texture_.draw(buf);
    draw(buf);
    return;
}
