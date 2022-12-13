#include "TextInsertWidget.h"

TextInsertWidget::TextInsertWidget(uint width, uint height):
    Widget(width, height), text_(){
        setTexture(Color(0, 15, 15));
    }

// TODO: we wanna know if spec number is pressed
void TextInsertWidget::onKeyPressed(const KeyPressedEvent* event){

    T_KEY key_val = event->key();
    if(key_val == T_KEY::BackSpace){
        text_.str().pop_back();
    }
    else if(key_val == T_KEY::Num1){
        text_.str().push_back('1');
    }
    else if (key_val == T_KEY::Num2){
        text_.str().push_back('2');
    }
    else if (key_val == T_KEY::Num3){
        text_.str().push_back('3');
    }
    else if (key_val == T_KEY::Num4){
        text_.str().push_back('4');
    }
    else if (key_val == T_KEY::Num5){
        text_.str().push_back('5');
    }
    else if (key_val == T_KEY::Num6){
        text_.str().push_back('6');
    }
    else if (key_val == T_KEY::Num7){
        text_.str().push_back('7');
    }
    else if (key_val == T_KEY::Num8){
        text_.str().push_back('8');
    }
    else if (key_val == T_KEY::Num9){
        text_.str().push_back('9');
    }
    else if (key_val == T_KEY::Num0){
        text_.str().push_back('0');
    }

    RequireRender();

    return;
}

void TextInsertWidget::draw(){
    text_.draw(this->GetPointerOnPixBuff());
    return;
}
