#include "Window.h"

Window::Window(Vector size):
    ContainerWidget(size),
    window_(CREATE_REAL_WINDOW(size))
{
    eventManager_ = new EventManager();

    // TODO: fix
    delete buffer_;
    buffer_ = window_->buffer();

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

    window_->open();
    bLayerDraw();
    window_->draw();

    while(window_->isOpen()){
        window_->extractEvents();

        if(!window_->extractedEvents.empty()){
            while(!window_->extractedEvents.empty()){
                const Event* event = window_->extractedEvents.front();
                window_->extractedEvents.pop();
                
                event->updateManipulatorsData();
                eventManager_->ProcessHandlers(event);
            }

            bLayerDraw();
            window_->draw();
        }
    }

    return;
}
