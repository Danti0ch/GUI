#ifndef CONTAINER_WIDGET_H
#define CONTAINER_WIDGET_H

#include "Widget.h"
#include <list>

class ContainerWidget : public Widget{
public:
    ContainerWidget(uint x, uint y, uint width, uint height);

    // TODO: mb virtual void?
    void draw() override;

    void connect( Widget* child_widget);
    void remove( Widget* child_widget);
    
    // TODO: fix    
    friend class Window;
private:
    std::list<Widget*> subwidgets_;

private:
    //! TODO: arg to container widget
    void connectDataUpdate_(Widget* container) override;
    void disconnectDataUpdate_() override;
};

#endif // CONTAINER_WIDGET_H
