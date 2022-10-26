#include "Widget.h"

// TODO: обернуть подобные конструкторы в один макрос
// TODO: дефолтный параметр для текстуры
ContainerWidget::ContainerWidget(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height):
    Widget(parent_widget, x, y, width, height), subwidgets_(){}

ContainerWidget::ContainerWidget(uint x, uint y, uint width, uint height):
    Widget(x, y, width, height), subwidgets_(){}

void ContainerWidget::draw(GraphicSpace* space){

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        (*subwidgets_iter)->fullDraw();
    }
    return;
}

void ContainerWidget::connect(Widget& child_widget){
    subwidgets_.push_back(&child_widget);
    child_widget.p_core_window_ = p_core_window_;
}

void ContainerWidget::remove(Widget& child_widget){
    subwidgets_.remove(&child_widget);
    child_widget.p_core_window_ = NULL;
}
