#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"
#include "Text.h"

// TODO: make field to variate font size, color and other stuff
class Label : public Widget{
public:
    Label(uint x, uint y, uint width, uint height):
        Widget(x, y, width, height),
        text_()
    {
        
        text_.color(Color(0, 0, 0));    
    }
    ~Label(){}

    // TODO: refactor
    void draw(){
        text_.draw(GetPointerOnPixBuff());
        return;
    }
    
    void text(const std::string& text){ text_.data(text);}
    const Text& text() const { return text_; }

private:

    Text text_;
};

#endif // LABEL_H
