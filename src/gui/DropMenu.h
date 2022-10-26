#include "Widget.h"
#include "Buttons.h"

class DropMenu : public RectButton{
public:
    DropMenu(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height);

    void addItem(const std::string& text);

    template<typename T_ARG>
    void addHandlerItem(uint item_id, T_EVENT event_id, T_HANDLER_FUNC p_handler, T_ARG arg){
        items_[item_id].addEventHandler<T_ARG>(event_id, p_handler, arg);
        return;
    }

    void addHandlerItem(uint item_id, T_EVENT event_id, T_HANDLER_FUNC p_handler);

    void removeHandlerItem(uint item_id, T_EVENT event_id, T_HANDLER_FUNC p_handler);
    
    void draw(GraphicSpace* space);
    bool is_expanded() const { return is_expanded_; }

    void setExpanded(bool mode){ is_expanded_ = mode; }

private:
    bool                    is_expanded_;
    ContainerWidget         dropped_area_;
    std::vector<RectButton> items_;
};
