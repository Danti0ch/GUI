#ifndef CONTAINER_WIDGET_H
#define CONTAINER_WIDGET_H

#include "Widget.h"
#include <list>

class ContainerWidget : public Widget{
public:
    ContainerWidget(uint x, uint y, uint width, uint height);

    virtual void draw() override;

    virtual void connect( Widget* child_widget);
    virtual void connect(Widget* child_widget, uint x, uint y);
    virtual void remove( Widget* child_widget);
    
    // TODO: fix    
    friend class Window;
protected:
    std::list<Widget*> subwidgets_;
private:
    void connectToManager_(EventManager* manager) override;
    void disconnectFromManager_() override;
};

#endif // CONTAINER_WIDGET_H
