#include "ContainerWidget.h"
#include <assert.h>

// TODO: обернуть подобные конструкторы в один макрос
// TODO: дефолтный параметр для текстуры
ContainerWidget::ContainerWidget(uint x, uint y, uint width, uint height):
    Widget(x, y, width, height), subwidgets_(){}

void ContainerWidget::draw(){

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->coreDraw();
        buff_.drawPixelBuffer((*subwidgets_iter)->x(), (*subwidgets_iter)->y(), (*subwidgets_iter)->pixBuff());
    }
    return;
}

void ContainerWidget::connect(Widget* child_widget){

    if(child_widget->parent_widget_ != NULL){
        child_widget->parent_widget_->remove(child_widget);
    }

    subwidgets_.push_back(child_widget);
    
    child_widget->parent_widget_ = this;

    assert(p_manager_ != NULL);

    child_widget->connectToManager_(p_manager_);
    return;
}

void ContainerWidget::remove(Widget* child_widget){
    subwidgets_.remove( child_widget);

    child_widget->parent_widget_ = NULL;
    child_widget->disconnectFromManager_();

    return;
}

#include <iostream>

void ContainerWidget::connectToManager_(EventManager* manager){

    if(p_manager_ != NULL){
        disconnectFromManager_();
    }

    manager->addWidget(this);
    std::cout << "555\n";
    p_manager_ = manager;

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->connectToManager_(manager);
    }
    return;
}

void ContainerWidget::disconnectFromManager_(){

    if(p_manager_ == NULL) return;

    p_manager_->removeWidget(this);
    p_manager_ = NULL;

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->disconnectFromManager_();
    }
    return;
}
