#include "Expended.h"

Expended::Expended(Vector size):
    ContainerWidget(size),
    expBuffer_(CREATE_RENDER_OBJECT(size)),
    hSlider_(new HSlider(size.x)),
    vSlider_(new VSlider(size.y - hSlider_->size().y)),
    expPos_(0, 0)
{
    connect(hSlider_, {0, 0});
    connect(vSlider_, {hSlider_->size().x - vSlider_->size().x, hSlider_->size().y});
    
    hSlider_->visible(false);
    vSlider_->visible(false);

    hSlider_->setHandler<Expended>(this, &Expended::horizontalMove);
    vSlider_->setHandler<Expended>(this, &Expended::verticalMove);
}

Expended::~Expended(){
    delete expBuffer_;

    delete hSlider_;
    delete vSlider_;
}

void Expended::setExpendedSize(Vector size){
    delete expBuffer_;

    expBuffer_ = CREATE_RENDER_OBJECT(size);

    requireRender();
    return;
}

void Expended::horizontalMove(double ratio){
    expPos_.x = expBuffer_->size().x * ratio;

    requireRender();
    return;
}

void Expended::verticalMove(double ratio){
    expPos_.y = expBuffer_->size().y * ratio;

    requireRender();
    return;
}

void Expended::draw(){

    buffer_->draw({0, 0}, expBuffer_, RectangleArea(expPos_, buffer_->size()));
    
    if(!(hSlider_->isVisible()) && (!vSlider_->isVisible())){
        buffer_->draw({0, 0}, expBuffer_, RectangleArea(expPos_, buffer_->size()));
        
        ContainerWidget::draw();
        return;
    }

    std::list<Widget*>::iterator iter = subwidgets_.begin(); 

    for (; iter != subwidgets_.end(); iter++){

        if(*iter == hSlider_ || *iter == vSlider_) continue;
        (*iter)->bLayerDraw();

        if((*iter)->isVisible()){
            expBuffer_->draw((*iter)->pos(), (*iter)->buffer_);
        }
    }

    buffer_->draw({0, 0}, expBuffer_, RectangleArea(expPos_, buffer_->size()));
    
    if(hSlider_->isVisible()){
        hSlider_->bLayerDraw();

        buffer_->draw(hSlider_->pos(), hSlider_->buffer_);
    }

    if(vSlider_->isVisible()){
        vSlider_->bLayerDraw();

        buffer_->draw(vSlider_->pos(), vSlider_->buffer_);
    }

    return;
}

void Expended::connect(Widget* child_widget, Vector pos){

    ContainerWidget::connect(child_widget, pos);

    Vector newExpSize;
    newExpSize.x  = std::max(expBuffer_->size().x,  child_widget->pos().x + child_widget->size().x);
    newExpSize.y  = std::max(expBuffer_->size().y,  child_widget->pos().y + child_widget->size().y);

    if(newExpSize.x > size().x){
        hSlider_->visible(true);
    }

    if(newExpSize.y > size().y){
        vSlider_->visible(true);
    }

    if(newExpSize.x > expBuffer_->size().x || newExpSize.y > expBuffer_->size().y){
        
        RenderObject* newExpBuffer = CREATE_RENDER_OBJECT(newExpSize);

        newExpBuffer->draw({0, 0}, expBuffer_);

        delete expBuffer_;
        expBuffer_ = newExpBuffer;
    }

    //?
    requireRender();    

    return;
}

void Expended::remove( Widget* child_widget){
    ContainerWidget::remove(child_widget);

    // TODO:
    return;
}

Vector Expended::subPos(const Widget* subwidget) const{
    if(subwidget == hSlider_ || subwidget == vSlider_) return subwidget->pos();

    std::list<Widget*>::const_iterator iter = std::find(subwidgets_.begin(), subwidgets_.end(), subwidget);

    if(iter == subwidgets_.end()) return VECTOR_POISON;

    return subwidget->pos() - expPos_;
}
