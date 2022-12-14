#include "Widget.h"
#include "Window.h"

Widget* Widget::FOCUSED_WIDGET = NULL;

Widget::Widget(Vector size):
    relPos_(), size_(size),
    is_focused_(false),
    is_visible_(true),
    is_render_required_(true),
    parent_widget_(NULL),
    window_(NULL),
    focusable_(true)
{
    bgLayer_ = CREATE_DRAWABLE_AREA(size);
    buffer_  = CREATE_RENDER_OBJECT(size);
}

Widget::~Widget(){
    delete bgLayer_;
    delete buffer_;
}

Vector Widget::realPos() const{
    if(parent_widget_ == NULL) return {0, 0};

    ContainerWidget* cur_parent = parent_widget_;
    Vector val = parent_widget_->subPos(this);

    while(cur_parent->parent() != NULL){
        val += cur_parent->parent()->subPos(cur_parent);
        cur_parent = cur_parent->parent();
    }

    return val;
}

Vector Widget::pos() const { return relPos_; }

Vector Widget::size() const { return size_; }

bool Widget::isFocused() const { return is_focused_; }
bool Widget::isVisible() const { return is_visible_; }

ContainerWidget* Widget::parent() { return parent_widget_; }

bool Widget::isRenderRequired(){ return is_render_required_; }

void Widget::x(coord val){
    relPos_.x = val;
}

void Widget::y(coord val){
    relPos_.y = val;
}

void Widget::pos(Vector val){
    relPos_ = val;
}

void Widget::visible(bool val){
    is_visible_ = val;
    requireRender();
}

void Widget::invertVisible(){
    visible(!is_visible_);
}

void Widget::texture(const std::string& path_to_img, bool framed){
    bgLayer_->drawImage(size(), path_to_img);
    if(framed)
        drawFrame(bgLayer_);
}

void Widget::texture(const Color& col, bool framed){
    bgLayer_->clear(col);
    if(framed)
        drawFrame(bgLayer_);
}

void Widget::requireRender(){
    is_render_required_ = true;

    ContainerWidget* parent = (parent_widget_);
    while(parent != NULL){
        
        parent->is_render_required_ = true;
        parent = parent->parent_widget_;
    }

    return;
}

void Widget::bLayerDraw(){
    if(!is_render_required_) return;

    buffer_->clear(Color(0, 0, 0, 0));
    buffer_->draw({0, 0}, bgLayer_);
    draw();

    is_render_required_ = false;
    return;
}

bool isPointInside(const Widget* widget, Vector pos){

    Vector realPos = widget->realPos();

    if(pos.x >= realPos.x && pos.x <= realPos.x + widget->size().x && pos.y >= realPos.y && pos.y <= realPos.y + widget->size().y){
        return true;
    } 
    return false;
}

bool isPointInside(const RectangleArea& rect, Vector pos){

    if(pos.x >= rect.pos.x && pos.x <= rect.pos.x + rect.size.x && pos.y >= rect.pos.y && pos.y <= rect.pos.y + rect.size.y){
        return true;
    } 
    return false;
}

void Widget::connectDataUpdate(ContainerWidget* container){

    if(window_ != NULL){
        disconnectDataUpdate( );
    }

    if(container->window_ == NULL){
        window_ = NULL;
        return;
    }

    container->window_->eventManager_->addWidget(this);
    window_ = container->window_;

    return;
}

void Widget::disconnectDataUpdate(){
    window_->eventManager_->removeWidget(this);
    window_ = NULL;

    return;
}

void Widget::connectBy(Widget* slotWidget, LINKAGE_MODE mode, uint indent_val, int offset){
    if(slotWidget->parent() == NULL){
        MDLOG("attempt to connect widget %p to widget %p, that isn't connected to container", this, slotWidget);
        return;
    }

    Vector pos = slotWidget->pos();
    
    if(mode == LINKAGE_MODE::TOP){
        pos.x += offset;
        pos.y += slotWidget->size().y + indent_val;
    }
    else if(mode == LINKAGE_MODE::BOTTOM){
        pos.x += offset;
        pos.y -= size().y + indent_val;    
    }
    else if(mode == LINKAGE_MODE::LEFT){
        pos.x -= size().y + indent_val;
        pos.y += offset;
    }
    else if(mode == LINKAGE_MODE::RIGHT){
        pos.x += slotWidget->size().x + indent_val;
        pos.y += offset;
    }

    slotWidget->parent()->connect(this, pos);

    return;
}

void Widget::triggerEvent(const Event* event){

    if(!isVisible()) return;
    
    if(event->type() == T_EVENT::mouseClick){

        if(!isPointInside(this, ManipulatorsContext::activeContext.mousePos())) return;

        if(focusable_){
            if(Widget::FOCUSED_WIDGET)
                Widget::FOCUSED_WIDGET->is_focused_ = false;

            is_focused_ = true;
            Widget::FOCUSED_WIDGET = this;
        }

        const MouseButtonPressedEvent* detected_event = static_cast<const MouseButtonPressedEvent*>(event);
        onMouseButtonPressed(detected_event);
    }
    else if(event->type() == T_EVENT::mouseReleased){
        //??/????
        //if(!isPointInside(this, ManipulatorsContext::activeContext.mousePos())) return;

        const MouseButtonReleasedEvent* detected_event = static_cast<const MouseButtonReleasedEvent*>(event);
        onMouseButtonReleased(detected_event);
    }
    else if(event->type() == T_EVENT::mouseMoved){

        const MouseMovedEvent* detected_event = static_cast<const MouseMovedEvent*>(event);
        onMouseMoved(detected_event);
    }
    else if(event->type() == T_EVENT::mouseWheelScrolled){

        if(!isFocused()) return;

        const MouseWheelScrolledEvent* detected_event = static_cast<const MouseWheelScrolledEvent*>(event);
        onMouseWheelScrolled(detected_event);
    }
    else if(event->type() == T_EVENT::keyPressed){
        if(!isFocused()) return;

        const KeyPressedEvent* detected_event = static_cast<const KeyPressedEvent*>(event);
        onKeyPressed(detected_event);
    }
    else if(event->type() == T_EVENT::keyReleased){
        if(!isFocused()) return;

        const KeyReleasedEvent* detected_event = static_cast<const KeyReleasedEvent*>(event);
        onKeyReleased(detected_event);
    }
    
    return;
}

Vector Widget::subPos(const Widget* subwidget) const{
    return VECTOR_POISON;
};
