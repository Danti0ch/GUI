#include "Label.h"

Label::Label(Vector size):
    Widget(size),
    text_()
{}

Label::Label(Vector size, const std::string& text):
    Widget(size),
    text_(text)
{}

void Label::draw(){

    // TODO: alignment
    buffer_->draw({5, 5}, text_);
    return;
}

void Label::text(const std::string& data){
    text_.str = data;

    requireRender();
    return;
}