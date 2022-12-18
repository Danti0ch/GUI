#include "Contexted.h"
#include "Window.h"

Contexted::Contexted(Vector size, unsigned int nItems):
    Widget(size),
    contextMenu_(new VListWidget({50, nItems * 30}))
{}

Contexted::~Contexted(){
    delete contextMenu_;
}

void Contexted::onMouseButtonPressed(const MouseButtonPressedEvent* event){
    if(event->tButton() == T_MOUSE_BUTTON::R){
        window_->drawContextMenu(ManipulatorsContext::activeContext.mousePos(), contextMenu_);
    }

    return;
}

void Contexted::addItem(const std::string& name, Action* action){
    contextMenu_->add(name, action);

    return;
}
