#include "Slider.h"
#include "TextureManager.h"

Slider::Slider(Vector size):
    Widget(size),
    ratio_(0),
    indicator_(NULL),
    actions_(new MacroAction())
{}

Slider::~Slider(){
    delete actions_;
    delete indicator_;
}

double Slider::ratio() const{ return ratio_; }

void Slider::indicatorMove(ORIENTATION orient){

    int cId = 0;
    if(orient == ORIENTATION::V) cId = 1;

    int newPos = (int)(ManipulatorsContext::activeContext.mousePos()[cId] - realPos()[cId]) - (int)(indicator_->size()[cId] / 2);

    if(newPos < 0) newPos = 0;
    else if(newPos + indicator_->size()[cId] > size()[cId]) newPos = size()[cId] - indicator_->size()[cId];

    ratio_ = (double)newPos / (double)(size()[cId] - indicator_->size()[cId]);

    actions_->execute();
    requireRender();

    return;
}

void Slider::drawIndicator(ORIENTATION orient){

    int cId = 0;
    if(orient == ORIENTATION::V) cId = 1;

    coord pos = (size()[cId] - indicator_->size()[cId]) * ratio_;

    Vector posToDraw(0, 0);

    posToDraw[cId] = pos;
    buffer_->draw(posToDraw, indicator_);

    return;
}

VSlider::VSlider(coord len):
    VSlider({10, len}){}

VSlider::VSlider(Vector size):
    Slider(size)
{
    indicator_ = CREATE_DRAWABLE_AREA(Vector(size.x, 20));
    bgLayer_->clear(Color(0x4a4a40, 100));
    indicator_->clear(0xcc31b2);
}

void VSlider::onMouseButtonPressed(const MouseButtonPressedEvent* event){
    
    indicatorMove(ORIENTATION::V);
    return;
}

void VSlider::onMouseMoved(const MouseMovedEvent* event){
    if(!isPointInside(this, ManipulatorsContext::activeContext.mousePos())){
        return;
    }

    if(!ManipulatorsContext::activeContext.isMouseLPressed()) return;
    
    indicatorMove(ORIENTATION::V);
    return;
}

void VSlider::draw(){
    drawIndicator(ORIENTATION::V);
    return;
}

coord VSlider::indicatorLen() const {
    return indicator_->size().y;
}

HSlider::HSlider(coord len):
    HSlider({len, 10}){}

HSlider::HSlider(Vector size):
    Slider(size)
{
    indicator_ = CREATE_DRAWABLE_AREA(Vector(20, size.y));
    bgLayer_->clear(Color(0x4a4a40, 100));
    indicator_->clear(0xcc31b2);
}

void HSlider::onMouseButtonPressed(const MouseButtonPressedEvent* event){

    indicatorMove(ORIENTATION::H);
    return;
}

void HSlider::onMouseMoved(const MouseMovedEvent* event){
    if(!isPointInside(this, ManipulatorsContext::activeContext.mousePos())){
        return;
    }
    
    if(!ManipulatorsContext::activeContext.isMouseLPressed()) return;
    
    indicatorMove(ORIENTATION::H);
    return;
}

void HSlider::draw(){
    drawIndicator(ORIENTATION::H);
    return;
}

coord HSlider::indicatorLen() const {
    return indicator_->size().x;
}

coord HSlider::len() const { return size().x; }
coord VSlider::len() const { return size().y; }
