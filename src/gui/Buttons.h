#ifndef ABSTRACT_BUTT_H
#define ABSTRACT_BUTT_H

#include "Text.h"

class AbstractButton : public Widget{
public:

    AbstractButton(ContainerWidget* p_widget, uint x, uint y, uint width, uint height):
        Widget(p_widget, x, y, width, height), text_(){}

    void draw(GraphicSpace* space) override{
        
        text_.draw(space, x() + 4, y() + height() / 2 - 5);
        return;
    }

    void setText(const Text& text){ text_ = text; }
    void setText(const std::string& text){ text_ = Text(text);}
private:
    Text text_;
};

class RectButton : public AbstractButton{
public:
    RectButton(ContainerWidget* p_widget, uint x, uint y, uint width, uint height):
        AbstractButton(p_widget, x, y, width, height){}

};

#endif // ABSTRACT_BUTT_H
