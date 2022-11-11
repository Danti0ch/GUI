#include "Widget.h"
#include "ContainerWidget.h"
#include <assert.h>

// TODO: добавить возможность дефолтного конструктора где параметры расположения будут подбираться автоматически?
Widget::Widget(uint x, uint y, uint width, uint height):
    x_(x), y_(y), width_(width), height_(height),
    rx_(x), ry_(y),
    is_focused_(false),
    is_visible_(true),
    is_render_required_(true),
    texture_(),
    buff_(width, height),
    parent_widget_(NULL),
    p_manager_(NULL)
{}

Widget::~Widget(){}
void Widget::coreDraw(){

    if(!is_render_required_) return;
    if(!is_visible_)         return;

    texture_.draw(&buff_, 0, 0, width_ - 1, height_ - 1);
    draw();

    is_render_required_ = false;
    return;
}

// TODO: copypaste with container widget
void Widget::connectDataUpdate_(Widget* container){

    if(p_manager_ != NULL){
        disconnectDataUpdate_( );
    }

    rx_ = x_ + container->rx();
    ry_ = y_ + container->ry();

    if(container->p_manager_ == NULL){
        p_manager_ = NULL;
        return;
    }
    container->p_manager_->addWidget(this);
    p_manager_ = container->p_manager_;

    return;
}

void Widget::disconnectDataUpdate_(){

    p_manager_->removeWidget(this);
    p_manager_ = NULL;

    return;
}

void Widget::triggerEvent(const Event* event){
    if(event->id() == T_EVENT::mouseLClick){
        const MouseLClickEvent* detected_event = static_cast<const MouseLClickEvent*>(event);
        onMouseLClick(detected_event);
    }
    else if(event->id() == T_EVENT::keyPressed){
        const KeyPressedEvent* detected_event = static_cast<const KeyPressedEvent*>(event);
        onKeyPressed(detected_event);
    }
    else if(event->id() == T_EVENT::sliderMoved){
        const SliderMovedEvent* detected_event = static_cast<const SliderMovedEvent*>(event);
        onSliderMoved(detected_event);
    }
    return;
}

void Widget::throwEvent(const Event* event){

    assert(event != NULL);
    p_manager_->ProcessHandlers(event);
    return;
}

void Widget::RequireRender(){

    is_render_required_ = true;

    ContainerWidget* parent = (parent_widget_);
    while(parent != NULL){

        parent->is_render_required_ = true;
        parent = parent->parent_widget_;
    }

    return;
}
