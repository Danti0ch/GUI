#ifndef CONTAINER_WIDGET_H
#define CONTAINER_WIDGET_H

class ContainerWidget : public Widget{
public:
    ContainerWidget(uint x, uint y, uint width, uint height);

    // TODO: mv virtual void?
    void draw(LocPixBuffer* core_window) override;

    friend class WidgetUnit;
private:
    std::list<Widget*> subwidgets_;
};

#endif // CONTAINER_WIDGET_H
