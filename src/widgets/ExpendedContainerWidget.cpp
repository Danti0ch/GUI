#include "ExpendedContainerWidget.h"

int a = 0;

// TODO: remove hardcode
ExpendedContainerWidget::ExpendedContainerWidget(uint width, uint height, uint sliderWidth):
    ContainerWidget(width, height),
    hSlider_(width, sliderWidth, width / 5),
    vSlider_(sliderWidth, height - sliderWidth, height / 5),
    loc_x_(0), loc_y_(0),
    ext_width_(width), ext_height_(height)
{       
    ContainerWidget::connect(&hSlider_, width - sliderWidth, sliderWidth);
    ContainerWidget::connect(&vSlider_, 0, 0);

    hSlider_.setVisible(false);
    vSlider_.setVisible(false);

    hSlider_.setTexture(Color(119, 136, 153));
    vSlider_.setTexture(Color(119, 136, 153));

    exp_buf_ = new PixelBuffer(width, height);
}

ExpendedContainerWidget::~ExpendedContainerWidget(){
    delete exp_buf_;
}

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

        PixelBuffer* buff = GetPointerOnPixBuff();
        buff->drawPixelBuffer(*exp_buf_, 0, 0, loc_x_, loc_y_, width(), height());
        
        ContainerWidget::draw();
        return;
    }

    // TODO: debug
    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){

        if(*subwidgets_iter == &hSlider_ || *subwidgets_iter == &vSlider_) continue;

        (*subwidgets_iter)->coreDraw();

        if((*subwidgets_iter)->isVisible()){
            exp_buf_->drawPixelBuffer((*subwidgets_iter)->x(), (*subwidgets_iter)->y(), (*subwidgets_iter)->pixBuff());
        }
    }

    PixelBuffer* buff = GetPointerOnPixBuff();

    buff->drawPixelBuffer(*exp_buf_, 0, 0, loc_x_, loc_y_, width(), height());
    
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

void ExpendedContainerWidget::connect( Widget* child_widget, uint x, uint y){
    NASSERT(child_widget);

    ContainerWidget::connect(child_widget, x, y);

    ext_width_  = std::max(ext_width_,  child_widget->x() + child_widget->width());
    ext_height_ = std::max(ext_height_, child_widget->y() + child_widget->height());

    if(ext_width_ > width()){
        hSlider_.setVisible( true);
    }

    if(ext_height_ > height()){
        vSlider_.setVisible(true);
    }

    if(ext_width_ > exp_buf_->width() || ext_height_ > exp_buf_->height()){
        PixelBuffer* p_tmp_buf = new PixelBuffer(std::max(ext_width_, exp_buf_->width()), std::max(ext_height_, exp_buf_->height()));

        p_tmp_buf->drawPixelBuffer(0, 0, *exp_buf_);

        delete exp_buf_;
        exp_buf_ = p_tmp_buf;
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

// TODO: what if child_widget not in list?? redone for handling error
uint ExpendedContainerWidget::getSubPosX(const Widget* child_widget) const{

    if(child_widget == &hSlider_ || child_widget == &vSlider_) return child_widget->x();

    std::list<Widget*>::const_iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        
        if((*subwidgets_iter) == child_widget){
            return (*subwidgets_iter)->x() - loc_x_;
        }
    }

    return -1;
}

uint ExpendedContainerWidget::getSubPosY(const Widget* child_widget) const{

    if(child_widget == &hSlider_ || child_widget == &vSlider_) return child_widget->y();

    std::list<Widget*>::const_iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        
        if((*subwidgets_iter) == child_widget){
            return (*subwidgets_iter)->y() - loc_y_;
        }
    }

    return -1;
}
/*
ExpendedContainerWidget::PixelBuffer* expBuf(){
    return exp_buf_;
}
*/

void ExpendedContainerWidget::connectDataUpdate_(Widget* container){
    ContainerWidget::connectDataUpdate_(container);
}

void ExpendedContainerWidget::disconnectDataUpdate_(){
    ContainerWidget::disconnectDataUpdate_();
}

const HSlider* ExpendedContainerWidget::pHSlider(){
    return &hSlider_;
}

const VSlider* ExpendedContainerWidget::pVSlider(){
    return &vSlider_;
}
