#include "BarWidget.h"

BarWidget::BarWidget(Vector size):
    ContainerWidget(size),
    activeDropped_(NULL)
{
    bgLayer_->transparency(0);
}

BarWidget::~BarWidget(){

    for(auto widget : droppedWidgets_){
        delete widget;
    }
}

void BarWidget::setDropped(uint nWidget){

    std::list<Widget*>::iterator iter = droppedWidgets_.begin();
    std::advance(iter, nWidget);

    Widget* selectedDropped = *iter;
    if(activeDropped_ == selectedDropped){
        activeDropped_->invertVisible();
        return;
    }

    (selectedDropped)->pos(countDroppedPos(nWidget));
    
    if(activeDropped_ != NULL){
        activeDropped_->visible(false);
    }

    selectedDropped->visible(true);
    activeDropped_ = selectedDropped;

    requireRender();

    return;
}

hBarWidget::hBarWidget(Vector size, bool isTop, coord listSize):
    BarWidget(size),
    list_(new HListWidget({size.x, listSize})),
    isTop_(isTop)
{   
    if(isTop_) connect(list_, {0, 0});
    else       connect(list_, {0, size.y - list_->size().y});
}

hBarWidget::~hBarWidget(){
    delete list_;
}

void hBarWidget::add(const std::string& label, Widget* widget){
    list_->add(label, new ObjArgAction<hBarWidget, uint>(this, &hBarWidget::setDropped, droppedWidgets_.size()));

    droppedWidgets_.push_back(widget);

    connect(widget, countDroppedPos(droppedWidgets_.size() - 1));

    widget->visible(false);
    return;
}

Vector hBarWidget::countDroppedPos(uint nDropped){
    
    std::list<Widget*>::iterator iter = droppedWidgets_.begin();
    std::advance(iter, nDropped);
    Widget* selectedDropped = *iter;

    const Widget* activelistItem = list_->items()[nDropped];

    Vector pos;
    if(isTop_){
        pos = {activelistItem->pos().x, list_->size().y};
    }
    else{
        pos = {activelistItem->pos().x, size().y - list_->size().y - selectedDropped->size().y};
    }

    if(activelistItem->pos().x + selectedDropped->size().x > size().x){
        pos.x = size().x - selectedDropped->size().x;
    }

    return pos;
}

vBarWidget::vBarWidget(Vector size, bool isRight, coord listSize):
    BarWidget(size),
    list_(new VListWidget({listSize, size.y})),
    isRight_(isRight)
{
    if(isRight_) connect(list_, {0, 0});
    else         connect(list_, {size.x - list_->size().x, 0});
}

vBarWidget::~vBarWidget(){
    delete list_;
}

void vBarWidget::add(const std::string& label, Widget* widget){
    list_->add(label, new ObjArgAction<vBarWidget, uint>(this, &vBarWidget::setDropped, droppedWidgets_.size()));

    droppedWidgets_.push_back(widget);

    connect(widget, countDroppedPos(droppedWidgets_.size() - 1));
    widget->visible(false);

    return;
}

Vector vBarWidget::countDroppedPos(uint nDropped){
    
    std::list<Widget*>::iterator iter = droppedWidgets_.begin();
    std::advance(iter, nDropped);
    Widget* selectedDropped = *iter;

    const Widget* activelistItem = list_->items()[nDropped];

    Vector pos;
    if(isRight_){
        pos = {activelistItem->pos().x + list_->size().x, activelistItem->size().y};
    }
    else{
        pos = {size().x - activelistItem->pos().x - selectedDropped->size().x, activelistItem->size().y};
    }

    if(activelistItem->pos().y + selectedDropped->size().y > size().y){
        pos.x = size().y - selectedDropped->size().y;
    }

    return pos;
}
