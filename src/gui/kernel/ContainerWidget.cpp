#include "Widget.h"

// TODO: обернуть подобные конструкторы в один макрос
// TODO: дефолтный параметр для текстуры
ContainerWidget::ContainerWidget(uint x, uint y, uint width, uint height):
    Widget(x, y, width, height), subwidgets_(){}

void ContainerWidget::draw(LocPixBuffer* buf){

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        
        LocPixBuffer cur_loc_buf(buf, (*subwidgets_iter)->x(), (*subwidgets_iter)->y(), (*subwidgets_iter)->width(), (*subwidgets_iter)->height());
        (*subwidgets_iter)->fullDraw(&cur_loc_buf);
    }
    return;
}

void ContainerWidget::connect(const Widget& child_widget){
    subwidgets_.push_back(&child_widget);
}

void ContainerWidget::remove(const Widget& child_widget){
    subwidgets_.remove(&child_widget);
}
