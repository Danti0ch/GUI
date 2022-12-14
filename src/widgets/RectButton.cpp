#include "Buttons.h"

RectButton::RectButton(Vector size):
    AbstractButton(size),
    Widget(size), // TODO: fix
    text_()
{}

RectButton::RectButton(Vector size, const std::string& label):
    AbstractButton(size),
    Widget(size),
    text_(label)
{}

void RectButton::draw(){
    buffer_->draw({5, 5}, text_);

    return;
}

const std::string& RectButton::label(){
    return text_.str;
}
