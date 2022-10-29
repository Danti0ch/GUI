#ifndef WIDGET_UNIT_H
#define WIDGET_UNIT_H

class WidgetUnit : public Widget{
public:
    WidgetUnit(uint x, uint y, uint width, uint height):
        Widget(x, y, width, height) {}
    
    void connect(ContainerWidget* parent){

        // TODO: poison?
        if(parent_widget_ != NULL) remove_connect();

        parent->subwidgets_.push_back(this);
        parent_widget_ = parent;
    }
    void remove_connect(){}
};

#endif // WIDGET_UNIT_H
