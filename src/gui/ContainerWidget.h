#ifndef CONTAINER_WIDGET_H
#define CONTAINER_WIDGET_H

// TODO: команды для манипулирования приоритезацией рисования
class ContainerWidget : public Widget{
 public:
    // TODO: дефолтный параметр для текстуры
    ContainerWidget(ContainerWidget* parent_widget, uint x, uint y, uint width, uint height);
    ContainerWidget(uint x, uint y, uint width, uint height);

    void draw(GraphicSpace* space) override;

    void connect(Widget& child_widget);
    void remove(Widget& child_widget);
private:
    std::list<Widget*> subwidgets_;
};

#endif // CONTAINER_WIDGET_H
