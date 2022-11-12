#include "ExpendedContainerWidget.h"

// TODO: remove hardcode
ExpendedContainerWidget::ExpendedContainerWidget(uint x, uint y, uint width, uint height, uint sliderWidth):
    ContainerWidget(x, y, width, height),
    hSlider_(x, y, width, sliderWidth, sliderWidth / 10),
    vSlider_(x + width - sliderWidth, y, sliderWidth, height, sliderWidth / 10),
    loc_x_(0), loc_y_(0),
    ext_width_(width), ext_height_(height)
{}

ExpendedContainerWidget::~ExpendedContainerWidget(){}

void ExpendedContainerWidget::onSliderMoved(const SliderMovedEvent* event){

    NASSERT(event);

    if(event->p_slider() == reinterpret_cast<Widget*>(&hSlider_)){
        //! type conversion could lead to errors
        loc_x_ = (uint)((double)(ext_width_ - width()) * event->ratio());
    }
    else if(event->p_slider() == reinterpret_cast<Widget*>(&vSlider_)){
        //! type conversion could lead to errors
        loc_y_ = (uint)((double)(ext_height_ - height()) * event->ratio());
    }

    return;
}

// TODO: draw widgets that partially fall into the area
void ExpendedContainerWidget::draw(){

    if(!(hSlider_.isVisible()) && (!vSlider_.isVisible())){
        ContainerWidget::draw();
        return;
    }

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){

        bool draw_required = false;
        if(hSlider_.isVisible() && vSlider_.isVisible()){
            if((*subwidgets_iter)->x() >= loc_x_ &&
               (*subwidgets_iter)->x() + (*subwidgets_iter)->width() <= width() - vSlider_.width() && 
               (*subwidgets_iter)->y() >= loc_y_ &&
               (*subwidgets_iter)->y() + (*subwidgets_iter)->height() <= height() - hSlider_.height()){
                
                draw_required =  true;
            }
        }
        else if(hSlider_.isVisible()){
            if((*subwidgets_iter)->x() >= loc_x_ &&
               (*subwidgets_iter)->x() + (*subwidgets_iter)->width() <= width()){

                draw_required =  true;
            }
        }
        else if(vSlider_.isVisible()){
            if((*subwidgets_iter)->y() >= loc_y_ &&
               (*subwidgets_iter)->y() + (*subwidgets_iter)->height() <= height()){

                draw_required =  true;
            }
        }

        if(draw_required){
            (*subwidgets_iter)->coreDraw();

            PixelBuffer* buff = GetPointerOnPixBuff();
            buff->drawPixelBuffer((*subwidgets_iter)->x() - loc_x_, (*subwidgets_iter)->y() - loc_y_, (*subwidgets_iter)->pixBuff());
        }
    }

    return;
}

void ExpendedContainerWidget::connect( Widget* child_widget){
    NASSERT(child_widget);

    ContainerWidget::connect(child_widget);

    ext_width_  = std::max(ext_width_,  child_widget->x());
    ext_height_ = std::max(ext_height_, child_widget->y());

    is_render_required_ = true;    

    return;
}

void ExpendedContainerWidget::remove(Widget* child_widget){

    NASSERT(child_widget);

    ContainerWidget::remove(child_widget);

    // TODO: to other func (find_max())

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        ext_width_  = std::max(ext_width_,  (*subwidgets_iter)->x());
        ext_height_ = std::max(ext_height_, (*subwidgets_iter)->y());
    }

    is_render_required_ = true;    

    return;
}
