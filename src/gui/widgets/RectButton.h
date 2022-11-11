#ifndef RECT_BUTTON_H
#define RECT_BUTTON_H

#include "AbstractButton.h"

template<typename T_HANDLER_ARG>
class RectButton : public AbstractButton<T_HANDLER_ARG>{
public:
    RectButton(uint x, uint y, uint width, uint height):
        AbstractButton<T_HANDLER_ARG>(x, y, width, height){}

    void setText(const std::string& str){
        text_.data(str);
    }
    
    virtual void draw() override{
        // TODO: count offset for text
        text_.draw(this->GetPointerOnPixBuff(), this->x() + 2, this->y() + 2);
        return;
    }

private:
    Text text_;
};

#endif // RECT_BUTTON_H
