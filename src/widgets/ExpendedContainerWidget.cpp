#include "ExpendedContainerWidget.h"

// TODO: remove hardcode
ExpendedContainerWidget::ExpendedContainerWidget(uint x, uint y, uint width, uint height, uint sliderWidth):
    ContainerWidget(x, y, width, height),
    hSlider_(0, 0, width, sliderWidth, width / 5),
    vSlider_(width - sliderWidth, sliderWidth, sliderWidth, height - sliderWidth, height / 5),
    loc_x_(0), loc_y_(0),
    ext_width_(width), ext_height_(height),
    exp_buf_(width, height)
{
    ContainerWidget::connect(&hSlider_);
    ContainerWidget::connect(&vSlider_);

    hSlider_.setVisible(false);
    vSlider_.setVisible(false);
}

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
    
    RequireRender();
    return;
}

// TODO: draw widgets that partially fall into the area
void ExpendedContainerWidget::draw(){


    // TODO: make test on this(check)
    if(!(hSlider_.isVisible()) && (!vSlider_.isVisible())){
        ContainerWidget::draw();
        return;
    }

    // TODO: debug
    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){

        if(*subwidgets_iter == &hSlider_ || *subwidgets_iter == &vSlider_) continue;
        bool draw_required = false;
        if(hSlider_.isVisible() && vSlider_.isVisible()){
            if(((*subwidgets_iter)->x() < loc_x_ + width() ||
                (*subwidgets_iter)->x() + (*subwidgets_iter)->width() >= loc_x_) && 
               ((*subwidgets_iter)->y() >= loc_y_ ||
                (*subwidgets_iter)->y() + (*subwidgets_iter)->height() <= height() - hSlider_.height())){
                
                draw_required =  true;
            }
        }
        
        else if(hSlider_.isVisible()){

            std::cout << (*subwidgets_iter)->x() << " " << (*subwidgets_iter)->width() << " " << loc_x_ << " " << width() << "\n";
            if(((*subwidgets_iter)->x() < loc_x_ + width()) ||
               ((*subwidgets_iter)->x() + (*subwidgets_iter)->width() >= loc_x_)){
                std::cout << "1\n";
                draw_required =  true;
            }
        }

        else if(vSlider_.isVisible()){
            if((*subwidgets_iter)->y() < loc_y_ + height() ||
               (*subwidgets_iter)->y() + (*subwidgets_iter)->height() >= loc_y_){

                draw_required =  true;
            }
        }

        if(draw_required && (*subwidgets_iter)->isVisible()){

            (*subwidgets_iter)->coreDraw();

            PixelBuffer* buff = GetPointerOnPixBuff();
            buff->drawPixelBuffer((*subwidgets_iter)->x() - loc_x_, (*subwidgets_iter)->y() - loc_y_, (*subwidgets_iter)->pixBuff());
        }
    }

    
    if(hSlider_.isVisible()){
        hSlider_.coreDraw();

        PixelBuffer* buff = GetPointerOnPixBuff();
        buff->drawPixelBuffer(hSlider_.x(), hSlider_.y(), (hSlider_.pixBuff()));
    }

    if(vSlider_.isVisible()){

        vSlider_.coreDraw();

        PixelBuffer* buff = GetPointerOnPixBuff();
        buff->drawPixelBuffer(vSlider_.x(), vSlider_.y(), (vSlider_.pixBuff()));
    }
    
    return;
}

void ExpendedContainerWidget::connect( Widget* child_widget){
    NASSERT(child_widget);

    ContainerWidget::connect(child_widget);

    ext_width_  = std::max(ext_width_,  child_widget->x());
    ext_height_ = std::max(ext_height_, child_widget->y());

    if(ext_width_ > width()){
       hSlider_.setVisible(true);
    }

    if(ext_height_ > height()){
        vSlider_.setVisible(true);
    }
    RequireRender();    

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

    RequireRender();

    return;
}

void ExpendedContainerWidget::ext_width(uint val){
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

void ExpendedContainerWidget::ext_height(uint val){
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
