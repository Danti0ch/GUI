#include "Widget.h"

// TODO: добавить возможность дефолтного конструктора где параметры расположения будут подбираться автоматически?
Widget::Widget(uint x, uint y, uint width, uint height):
    x_(x), y_(y), width_(width), height_(height),
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

    texture_.draw(&buff_, 0, 0, width_, height_);
    draw();

    is_render_required_ = false;
    return;
}

// TODO: copypaste with container widget
void Widget::connectToManager_(EventManager* manager){

    if(p_manager_ != NULL){
        disconnectFromManager_( );
    }

    p_manager_->addWidget(this);
    p_manager_ = manager;

    return;
}

void Widget::disconnectFromManager_(){

    p_manager_->removeWidget(this);
    p_manager_ = NULL;

    return;
}
void Widget::triggerEvent(const Event* event){
    if(event->id() == T_EVENT::mouseLClick){
        onMouseLClick(event);
    }
    else if(event->id() == T_EVENT::keyPressed){
        onKeyPressed(event);
    }

    return;
}

void Widget::x(uint val){
    x_ = val;
    is_render_required_ = true;
    return;
}

void Widget::y(uint val){
    y_ = val;
    is_render_required_ = true;
    return;
}
