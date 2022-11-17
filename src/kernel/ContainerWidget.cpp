#include "Widget.h"
#include <assert.h>

// TODO: обернуть подобные конструкторы в один макрос
// TODO: дефолтный параметр для текстуры
ContainerWidget::ContainerWidget(uint x, uint y, uint width, uint height):
    Widget(x, y, width, height), subwidgets_(){}

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

    connect(child_widget, x, y);
    return;
}

void ContainerWidget::connect(Widget* child_widget){
    assert(child_widget != NULL);

    if(child_widget->parent_widget_ != NULL){
        child_widget->parent_widget_->remove(child_widget);
    }

    subwidgets_.push_back(child_widget);
    
    child_widget->parent_widget_ = this;

    child_widget->connectDataUpdate_(this);
    return;
}

void ContainerWidget::remove(Widget* child_widget){
    subwidgets_.remove( child_widget);

    child_widget->parent_widget_ = NULL;
    child_widget->disconnectDataUpdate_();

    return;
}

void ContainerWidget::connectDataUpdate_(Widget* container){

    if(p_manager_ != NULL){
        disconnectDataUpdate_();
    }

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
