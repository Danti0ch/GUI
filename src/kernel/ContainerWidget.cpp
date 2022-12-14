#include "Widget.h"
#include "Window.h"

ContainerWidget::ContainerWidget(Vector size):
    Widget(size), subwidgets_()
{
    focusable_ = false;
}

void ContainerWidget::draw(){

    std::list<Widget*>::iterator subwidgets_iter;
    
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        if((*subwidgets_iter)->isVisible()){

            (*subwidgets_iter)->bLayerDraw();
            buffer_->draw((*subwidgets_iter)->relPos_, (*subwidgets_iter)->buffer_);
        }
    }
    return;
}

void ContainerWidget::connect(Widget* child_widget, Vector pos){
    NASSERT(child_widget);

    child_widget->pos(pos);

    if(child_widget->parent_widget_ != NULL){
        child_widget->parent_widget_->remove(child_widget);
    }

    subwidgets_.push_back(child_widget);    
    child_widget->parent_widget_ = this;

    child_widget->connectDataUpdate(this);

    return;
}

void ContainerWidget::remove(Widget* child_widget){

    subwidgets_.remove( child_widget);

    child_widget->parent_widget_ = NULL;
    child_widget->disconnectDataUpdate();

    child_widget->pos(VECTOR_POISON);
    
    return;
}

void ContainerWidget::connectDataUpdate(ContainerWidget* container){

    if(window_ != NULL){
        disconnectDataUpdate();
    }

    if(container->window_ == NULL) return;

    container->window_->eventManager_->addWidget(this);
    window_ = container->window_;

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->connectDataUpdate(this);
    }

    return;
}

void ContainerWidget::disconnectDataUpdate(){

    if(window_ == NULL) return;

    window_->eventManager_->removeWidget(this);
    window_ = NULL;

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->disconnectDataUpdate();
    }
    return;
}

Vector ContainerWidget::subPos(const Widget* subwidget) const{

    std::list<Widget*>::const_iterator iter = std::find(subwidgets_.begin(), subwidgets_.end(), subwidget);

    if(iter == subwidgets_.end()) return VECTOR_POISON;

    return subwidget->pos();
}
