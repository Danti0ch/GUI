#include "DropMenu.h"

static void change_expanded(Event* event, void* p_menu);

DropMenu::DropMenu(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height):
    RectButton(parent_widget, x, y, width, height), dropped_area_(x, y - height, width, 0), is_expanded_(false){
        this->addEventHandler<DropMenu*>(T_EVENT::mouseLClickEvent, change_expanded, this);
    }
//----------------------------------------------------------------------------------------//

void DropMenu::addItem(const std::string& text){

    items_.push_back(RectButton(&dropped_area_, dropped_area_.x(), dropped_area_.y() - height(), dropped_area_.width(), height()));
    items_[items_.size() - 1].setText(text);
    dropped_area_.resize(dropped_area_.x(), dropped_area_.y() - height(), dropped_area_.width(), dropped_area_.height() + height());
    dropped_area_.connect(items_.back());

    return;
}
//----------------------------------------------------------------------------------------//

void DropMenu::addHandlerItem(uint item_id, T_EVENT event_id, T_HANDLER_FUNC p_handler){
    items_[item_id].addEventHandler(event_id, p_handler);
    return;
}
//----------------------------------------------------------------------------------------//

void DropMenu::removeHandlerItem(uint item_id, T_EVENT event_id, T_HANDLER_FUNC p_handler){
    items_[item_id].RemoveEventHandler(event_id, p_handler);
    return;
}
//----------------------------------------------------------------------------------------//

void DropMenu::draw(GraphicSpace* space){

    RectButton::draw(space);
    if(!is_expanded_) return;

    dropped_area_.fullDraw();
    return;    
}
//----------------------------------------------------------------------------------------//

static void change_expanded(Event* event, void* p_menu){

    DropMenu* menu = static_cast<DropMenu*>(p_menu);

    menu->setExpanded(!menu->is_expanded());
    return;
}
