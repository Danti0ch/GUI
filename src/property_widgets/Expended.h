#ifndef EXPENDED_H
#define EXPENDED_H

#include "Widget.h"
#include "Slider.h"

class Expended : public ContainerWidget{
public:
    Expended(Vector size);
    ~Expended();

    virtual void draw() override;
    void setExpendedSize(Vector size);

protected:
    void connect(Widget* child_widget, Vector pos) override;
    void remove( Widget* child_widget) override;

    Vector subPos(const Widget* subwidget) const override;
private:
    void horizontalMove(double ratio);
    void verticalMove(double ratio);

private:
    RenderObject* expBuffer_;

    HSlider* hSlider_;
    VSlider* vSlider_;

    Vector expPos_;
};

#endif // EXPENDED_H
