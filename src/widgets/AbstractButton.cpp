#include "Buttons.h"

AbstractButton::AbstractButton(Vector size):
    Widget(size),
    Hovered(size, 0xf3a2f5, 0x8907fa),
    actions_(new MacroAction())
{
    bgLayer_->clear(0xa69ead);
}

AbstractButton::~AbstractButton(){
    delete actions_;
}

void AbstractButton::onMouseButtonPressed(const MouseButtonPressedEvent* event){
    Hovered::onMouseButtonPressed(event);
    
    if(isPointInside(this, ManipulatorsContext::activeContext.mousePos())){
        actions_->execute();
    }
    return;
}

void AbstractButton::addHandler(Action* action){
    actions_->add(action);

    return;
}
