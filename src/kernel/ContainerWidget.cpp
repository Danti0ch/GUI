#include "Widget.h"
#include <assert.h>

// TODO: обернуть подобные конструкторы в один макрос
// TODO: дефолтный параметр для текстуры
ContainerWidget::ContainerWidget(uint width, uint height):
    Widget(width, height), subwidgets_(){ }

void ContainerWidget::draw(){

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->coreDraw();

        if((*subwidgets_iter)->isVisible()){
            buff_.drawPixelBuffer((*subwidgets_iter)->x(), (*subwidgets_iter)->y(), (*subwidgets_iter)->pixBuff());
        }
    }
    return;
}

void ContainerWidget::connect(Widget* child_widget, uint x, uint y){
    NASSERT(child_widget);
    
    child_widget->x(x);
    child_widget->y(y);

    if(child_widget->parent_widget_ != NULL){
        child_widget->parent_widget_->remove(child_widget);
    }

    subwidgets_.push_back(child_widget);
    
    child_widget->parent_widget_ = this;

    child_widget->connectDataUpdate_(this);

    return;
}

// TODO: or make widget->connect() ??
void ContainerWidget::connect(Widget* new_widget, Widget* from_widget, LINKAGE_MODE mode, uint indent_val, uint offset){

    if(from_widget->parent() == NULL) return;
    
    bool from_widget_found = false;
    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        if(*subwidgets_iter == from_widget) from_widget_found = true;
    }

    uint x_coord = 0, y_coord = 0;

    if(mode == LINKAGE_MODE::TOP){
        x_coord = from_widget->x() + offset;
        y_coord = from_widget->y() + from_widget->height() + indent_val;
    }
    else if(mode == LINKAGE_MODE::BOTTOM){
        x_coord = from_widget->x() + offset;
        y_coord = from_widget->y() - new_widget->height() - indent_val;    
    }
    else if(mode == LINKAGE_MODE::LEFT){
        x_coord = from_widget->x() - new_widget->width() - indent_val;
        y_coord = from_widget->y() + offset;
    }
    else if(mode == LINKAGE_MODE::RIGHT){
        x_coord = from_widget->x() + from_widget->width() + indent_val;
        y_coord = from_widget->y() + offset;
    }

    this->connect(new_widget, x_coord, y_coord);
    return;
}

void ContainerWidget::remove(Widget* child_widget){

    subwidgets_.remove( child_widget);

    child_widget->parent_widget_ = NULL;
    child_widget->disconnectDataUpdate_();

    child_widget->x(POS_POISON);
    child_widget->y(POS_POISON);
    
    return;
}

void ContainerWidget::connectDataUpdate_(Widget* container){

    if(p_manager_ != NULL){
        disconnectDataUpdate_();
    }
    if(container->p_manager_ == NULL) return;

    container->p_manager_->addWidget(this);
    p_manager_ = container->p_manager_;

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->connectDataUpdate_(this);
    }

    return;
}

void ContainerWidget::disconnectDataUpdate_(){

    if(p_manager_ == NULL) return;

    p_manager_->removeWidget(this);
    p_manager_ = NULL;

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->disconnectDataUpdate_();
    }
    return;
}

// TODO: what if child_widget not in list?? redone for handling error
uint ContainerWidget::getSubPosX(const Widget* child_widget) const{

    std::list<Widget*>::const_iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        
        if((*subwidgets_iter) == child_widget){
            return (*subwidgets_iter)->x();
        }
    }

    return -1;
}

uint ContainerWidget::getSubPosY(const Widget* child_widget) const{

    std::list<Widget*>::const_iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        
        if((*subwidgets_iter) == child_widget){
            return (*subwidgets_iter)->y();
        }
    }

    return -1;
}
