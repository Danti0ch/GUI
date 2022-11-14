#include "ExpendedWidget.h"

ExpendedWidget::ExpendedWidget(uint x, uint y, uint width, uint height, uint sliderWidth):
    Widget(x, y, width, height),
    hSlider_(0, 0, width, sliderWidth, width / 4),
    vSlider_(width - sliderWidth, 0, sliderWidth, height, height / 4),
    loc_x_(0), loc_y_(0),
    ext_width_(width), ext_height_(height)
{
    hSlider_.setTexture(Color(0, 255, 255));
    vSlider_.setTexture(Color(0, 255, 255));
}

ExpendedWidget::~ExpendedWidget(){}

void ExpendedWidget::onSliderMoved(const SliderMovedEvent* event){

    NASSERT(event);

     "SLIDER_MOVED\n";
    if(event->p_slider() == reinterpret_cast<Widget*>(&hSlider_)){
        //! type conversion could lead to errors
        loc_x_ = (uint)((double)(ext_width_ - width()) * event->ratio());
    }
    else if(event->p_slider() == reinterpret_cast<Widget*>(&vSlider_)){
        //! type conversion could lead to errors
        loc_y_ = (uint)((double)(ext_height_ - height()) * event->ratio());
    }

    RequireRender();
    return;
}

void ExpendedWidget::ext_width(uint val){
    ext_width_ = val;

    if(ext_width_ <= width()){
        hSlider_.setVisible(false);
    }
    else{
        hSlider_.setVisible(true);
        hSlider_.ratio((double)loc_x_ / (double)(ext_width_ - width()));
    }

    return;
}

void ExpendedWidget::ext_height(uint val){
    ext_height_ = val;

    if(ext_height_ <= height()){
        vSlider_.setVisible(false);
    }
    else{
        vSlider_.setVisible(true);
        vSlider_.ratio((double)loc_y_ / (double)(ext_height_ - height()));
    }

    return;
}

// TODO: draw widgets that partially fall into the area
void ExpendedWidget::draw(){

    if(ext_width_ > width()){
        hSlider_.coreDraw();

        PixelBuffer* p_buf = GetPointerOnPixBuff();
        p_buf->drawPixelBuffer(hSlider_.x(), hSlider_.y(), hSlider_.pixBuff());    
    }
    if(ext_height_ > height()){
        vSlider_.coreDraw();

        PixelBuffer* p_buf = GetPointerOnPixBuff();
        p_buf->drawPixelBuffer(vSlider_.x(), vSlider_.y(), vSlider_.pixBuff());    
    }

    return;
}

/*
// TODO: draw widgets that partially fall into the area
void ExpendedWidget::draw(){

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
*/
