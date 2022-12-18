#include "Window.h"

Window::Window(Vector size):
    ContainerWidget(size),
    realWindow_(CREATE_REAL_WINDOW(size)),
    eventManager_(new EventManager())
{

    window_ = this;
    // TODO: fix
    delete buffer_;
    buffer_ = realWindow_->buffer();

    bgLayer_->clear(0xbd87c4);
}

Window::~Window(){
    delete window_;
    delete eventManager_;
}

void Window::add(Widget* widget, Vector pos){
    ContainerWidget::connect(widget, pos);
    return;
}

void Window::remove(Widget* widget){
    ContainerWidget::remove(widget);
    return;
}

void Window::exec(){

    realWindow_->open();
    bLayerDraw();
    window_->draw();

    while(realWindow_->isOpen()){
        realWindow_->extractEvents();

        if(!realWindow_->extractedEvents.empty()){
            while(!realWindow_->extractedEvents.empty()){
                const Event* event = realWindow_->extractedEvents.front();
                realWindow_->extractedEvents.pop();
                
                event->updateManipulatorsData();
                eventManager_->ProcessHandlers(event);
            }

            bLayerDraw();
            realWindow_->draw();
        }
    }

    return;
}

void Window::drawContextMenu(Vector pos, VListWidget* menu){
    
    if(pos.y < menu->size().y){
        pos.y = menu->size().y;
    }
    if(pos.x + menu->size().x > size().x){
        pos.x = size().x - menu->size().x;
    }

    pos.y -= menu->size().y;
    connect(menu, pos);
    activeContextMenu_ = menu;

    return;
}

void Window::onMouseButtonPressed(const MouseButtonPressedEvent* event){

    if(isPointInside(activeContextMenu_, ManipulatorsContext::activeContext.mousePos())){
        remove(activeContextMenu_);
        activeContextMenu_= NULL;
    }

    return;
}
