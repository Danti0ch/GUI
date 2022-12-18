#include "Slider.h"
#include "TextureManager.h"

Slider::Slider(Vector size, ORIENTATION orient, ProportionRatio initRatio):
    Widget(size),
    ratio_(initRatio),
    indicator_(NULL),
    actions_(new MacroAction()),
    orient_(orient)
{}

Slider::~Slider(){
    delete actions_;
    delete indicator_;
}

double Slider::ratio() const{ return ratio_; }

void Slider::indicatorMove(){

    int cId = 0;
    if(orient_ == ORIENTATION::V) cId = 1;

    int newPos = (int)(ManipulatorsContext::activeContext.mousePos()[cId] - realPos()[cId]) - (int)(indicator_->size()[cId] / 2);

    if(newPos < 0) newPos = 0;
    else if(newPos + indicator_->size()[cId] > size()[cId]) newPos = size()[cId] - indicator_->size()[cId];

    ratio_ = (double)newPos / (double)(size()[cId] - indicator_->size()[cId]);

    actions_->execute();
    requireRender();

    return;
}

void Slider::drawIndicator(){

    int cId = 0;
    if(orient_ == ORIENTATION::V) cId = 1;

    coord pos = (size()[cId] - indicator_->size()[cId]) * ratio_;

    Vector posToDraw(0, 0);

    posToDraw[cId] = pos;
    buffer_->draw(posToDraw, indicator_);

    return;
}

void Slider::replaceIndicator(ProportionRatio ratio){
    ratio_ = ratio;
    drawIndicator();
    requireRender();
}

VSlider::VSlider(coord len, ProportionRatio initRatio):
    VSlider({10, len}, initRatio){}

VSlider::VSlider(Vector size, ProportionRatio initRatio):
    Slider(size, ORIENTATION::V, initRatio)
{
    indicator_ = CREATE_DRAWABLE_AREA(Vector(size.x, 20));

    texture(Color(0x4a4a40, 100));
    indicator_->clear(0xcc31b2);

    if(ratio_ > 0)
        drawIndicator();
}

void VSlider::onMouseButtonPressed(const MouseButtonPressedEvent* event){
    
    indicatorMove();
    ACTIVE_SLIDER = this;
    return;
}

void VSlider::onMouseButtonReleased(const MouseButtonReleasedEvent* event){
    ACTIVE_SLIDER = NULL;
}

void VSlider::onMouseMoved(const MouseMovedEvent* event){
    if(this != Slider::ACTIVE_SLIDER) return;

    if(!ManipulatorsContext::activeContext.isMouseLPressed()) return;
    
    indicatorMove();
    return;
}

void VSlider::draw(){
    drawIndicator();
    return;
}

coord VSlider::indicatorLen() const {
    return indicator_->size().y;
}

HSlider::HSlider(coord len, ProportionRatio initRatio):
    HSlider({len, 10}, initRatio){}

HSlider::HSlider(Vector size, ProportionRatio initRatio):
    Slider(size, ORIENTATION::H, initRatio)
{
    indicator_ = CREATE_DRAWABLE_AREA(Vector(20, size.y));
    texture(Color(0x4a4a40, 100));
    indicator_->clear(0xcc31b2);

    if(ratio_ > 0)
        drawIndicator();
}

void HSlider::onMouseButtonPressed(const MouseButtonPressedEvent* event){

    indicatorMove();
    ACTIVE_SLIDER = this;
    return;
}

void HSlider::onMouseButtonReleased(const MouseButtonReleasedEvent* event){
    ACTIVE_SLIDER = NULL;
}

void HSlider::onMouseMoved(const MouseMovedEvent* event){
 
    if(!ManipulatorsContext::activeContext.isMouseLPressed()) return;
    if(this != Slider::ACTIVE_SLIDER) return;

    indicatorMove();
    return;
}

void HSlider::draw(){
    drawIndicator();
    return;
}

coord HSlider::indicatorLen() const {
    return indicator_->size().x;
}

coord HSlider::len() const { return size().x; }
coord VSlider::len() const { return size().y; }

Slider* Slider::ACTIVE_SLIDER = NULL;
