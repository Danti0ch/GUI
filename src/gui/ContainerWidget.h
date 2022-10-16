#ifndef CONTAINTER_WIDGET_H
#define CONTAINTER_WIDGET_H

class ContainerWidget : public Widget{

    ContainerWidget(uint x, uint y, uint width, uint height):
        Widget(x, y, width, height),
        subwidgets_()
    {}

    void Draw() override{
        for(uint n_wid = 0; n_wid < subwidgets_.size(); n_wid++){
            subwidgets_[n_wid].Draw();
        }
        return;
    }
    
private:
    vector<Widget*> subwidgets_;
};

#endif  // CONTAINTER_WIDGET_H
