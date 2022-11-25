#ifndef RECT_BUTTON_H
#define RECT_BUTTON_H

#include "AbstractButton.h"

template<class T_RECEIVER, typename T_HANDLER_ARG>
class RectButton : public AbstractButton<T_RECEIVER, T_HANDLER_ARG>{
public:
    RectButton(uint x, uint y, uint width, uint height):
        AbstractButton<T_RECEIVER, T_HANDLER_ARG>(x, y, width, height){}

    // TODO: redone
    RectButton(const RectButton<T_RECEIVER, T_HANDLER_ARG>& other):
        AbstractButton<T_RECEIVER, T_HANDLER_ARG>(static_cast<const AbstractButton<T_RECEIVER, T_HANDLER_ARG>&>(other)),
        text_(other.text_){}

    void setText(const std::string& str){
        text_.data(str);
    }
    
    virtual void draw() override{
        // TODO: count offset for text

        text_.draw(this->GetPointerOnPixBuff(), 2, 6);
        return;
    }

private:
    Text text_;
};

#endif // RECT_BUTTON_H
