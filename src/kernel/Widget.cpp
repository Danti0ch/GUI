#include "Widget.h"

// TODO: добавить возможность дефолтного конструктора где параметры расположения будут подбираться автоматически?
Widget::Widget(uint width, uint height):
    x_(POS_POISON), y_(POS_POISON), width_(width), height_(height),
    is_focused_(false),
    is_visible_(true),
    is_render_required_(true),
    texture_(),
    buff_(width, height),
    parent_widget_(NULL),
    p_manager_(NULL)
{
}

Widget::~Widget(){}
void Widget::coreDraw(){

    if(!is_render_required_) return;

    buff_.clear(Color(255, 255, 255, 0));
    texture_.draw(&buff_, 0, 0, width_, height_);
    draw();

    is_render_required_ = false;
    return;
}

// TODO: copypaste with container widget
void Widget::connectDataUpdate_(Widget* container){

    if(p_manager_ != NULL){
        disconnectDataUpdate_( );
    }

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
    if(event->type() == T_EVENT::mouseLClick){
        const MouseLClickEvent* detected_event = static_cast<const MouseLClickEvent*>(event);
        onMouseLClick(detected_event);
    }
    else if(event->type() == T_EVENT::keyPressed){
        const KeyPressedEvent* detected_event = static_cast<const KeyPressedEvent*>(event);
        onKeyPressed(detected_event);
    }
    else if(event->type() == T_EVENT::sliderMoved){
        const SliderMovedEvent* detected_event = static_cast<const SliderMovedEvent*>(event);
        onSliderMoved(detected_event);
    }
    else if(event->type() == T_EVENT::mouseMoved){
        const MouseMovedEvent* detected_event = static_cast<const MouseMovedEvent*>(event);
        onMouseMoved(detected_event);
    }
    else if(event->type() == T_EVENT::mouseReleased){
        const MouseReleasedEvent* detected_event = static_cast<const MouseReleasedEvent*>(event);
        onMouseReleased(detected_event);
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

// TODO: make non-recursive
uint Widget::real_x() const{

    if(parent_widget_ == NULL) return 0;

    return parent_widget_->getSubPosX(this) + parent_widget_->real_x();
}

uint Widget::real_y() const{

    if(parent_widget_ == NULL) return 0;

    return parent_widget_->getSubPosY(this) + parent_widget_->real_y();
}

bool isPointInside(const Widget* widget, uint x, uint y){

    uint realX = widget->real_x(), realY = widget->real_y();

    if(x >= realX && x <= realX + widget->width() && y >= realY && y <= realY + widget->height()){
        return true;
    } 
    return false;
}

uint Widget::x() const { return x_; }
uint Widget::y() const { return y_; }

uint Widget::width() const { return width_; }
uint Widget::height() const { return height_; }

bool Widget::isFocused() const { return is_focused_; }
bool Widget::isVisible() const { return is_visible_; }
bool Widget::isRenderRequired() { return is_render_required_; }
Texture& Widget::texture(){ return texture_; }

void Widget::setTexture(const Texture& texture){ texture_ = texture; }

// TODO: make it virtual for overloading in containerWidget
void Widget::setVisible(bool val){

    if(isVisible() != val){
        RequireRender();
    }
    is_visible_ = val;
}

ContainerWidget* Widget::parent() { return parent_widget_; }
const PixelBuffer& Widget::pixBuff() const { return buff_; }

//! normal?? + rename
PixelBuffer* Widget::GetPointerOnPixBuff() { return &buff_; }


void Widget::changeVisible(bool def_val){
    is_visible_ = !is_visible_;
    return;
}
