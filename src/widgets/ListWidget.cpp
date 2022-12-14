#include "ListWidget.h"

const int HLIST_ITEM_LEN = 50;
const int VLIST_ITEM_LEN = 30;

AbstractListWidget::AbstractListWidget(Vector size, coord itemLen):
    Expended(size),
    items_(),
    itemLen_(itemLen)
{
    bgLayer_->clear(0xe2c5e6);
}

AbstractListWidget::~AbstractListWidget(){
    for(auto item : items_){
        delete item;
    }
}

void AbstractListWidget::add(ORIENTATION orient, const std::string& name){

    RectButton* butt = NULL;

    if(orient == ORIENTATION::H){
        butt = new RectButton({HLIST_ITEM_LEN, size().y}, name);
        Expended::connect(butt, {items_.size() * HLIST_ITEM_LEN, 0});
    }
    else{
        butt = new RectButton({size().x, VLIST_ITEM_LEN}, name);
        Expended::connect(butt, {0, items_.size() * VLIST_ITEM_LEN});
    }

    items_.push_back(butt);

    return;
}

void AbstractListWidget::add(ORIENTATION orient, const std::string& name, Action* action){
    add(orient, name);

    items_.back()->addHandler(action);

    return;
}

void AbstractListWidget::setHandler(const std::string& name, Action* action){

    for(int n_item = 0; n_item < items_.size(); n_item++){
        if(items_[n_item]->label() == name){
            items_[n_item]->addHandler(action);
            return;
        }
    }

    delete action;
    MDLOG("item \"%s\" not found in list %p", name, this);
    return;
}

std::vector<RectButton*>& AbstractListWidget::items(){
    return items_;
}

HListWidget::HListWidget(Vector size):
    AbstractListWidget(size, HLIST_ITEM_LEN)
{}
HListWidget::HListWidget(Vector size, coord itemLen):
    AbstractListWidget(size, itemLen)
{}

void HListWidget::add(const std::string& name){
    AbstractListWidget::add(ORIENTATION::H, name);
}

void HListWidget::add(const std::string& name, Action* action){
    AbstractListWidget::add(ORIENTATION::H, name, action);
}

VListWidget::VListWidget(Vector size):
    AbstractListWidget(size, VLIST_ITEM_LEN)
{}
VListWidget::VListWidget(Vector size, coord itemLen):
    AbstractListWidget(size, itemLen)
{}

void VListWidget::add(const std::string& name){
    AbstractListWidget::add(ORIENTATION::V, name);
}

void VListWidget::add(const std::string& name, Action* action){
    AbstractListWidget::add(ORIENTATION::V, name, action);
}
