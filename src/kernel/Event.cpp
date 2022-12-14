#include "Event.h"

ManipulatorsContext::ManipulatorsContext():
    isKeyPressed_(N_KEYS, 0),
    isMouseLPressed_(false),
    isMouseRPressed_(false)
{}

ManipulatorsContext::~ManipulatorsContext(){}

bool ManipulatorsContext::isKeyPressed(T_KEY key) const { return static_cast<bool>(isKeyPressed_[static_cast<int>(key)]); }

bool ManipulatorsContext::isMouseLPressed() const { return isMouseLPressed_; }
bool ManipulatorsContext::isMouseRPressed() const { return isMouseRPressed_; }

Vector ManipulatorsContext::mousePos() const { return mousePos_; }

Event::Event(T_EVENT type):
    type_(type){}
Event::~Event(){}

T_EVENT Event::type() const{
    return type_;
}

MouseButtonPressedEvent::MouseButtonPressedEvent(T_MOUSE_BUTTON tButton):
    Event(T_EVENT::mouseClick),
    tButton_(tButton)
{}

void MouseButtonPressedEvent::updateManipulatorsData() const{
    if(tButton_ == T_MOUSE_BUTTON::L)
        ManipulatorsContext::activeContext.isMouseLPressed_ = true;
    else
        ManipulatorsContext::activeContext.isMouseRPressed_ = true;
}

T_MOUSE_BUTTON MouseButtonPressedEvent::tButton() const{ return tButton_; }
//____________________________________________________________________

MouseButtonReleasedEvent::MouseButtonReleasedEvent(T_MOUSE_BUTTON tButton):
    Event(T_EVENT::mouseReleased),
    tButton_(tButton)
{}

void MouseButtonReleasedEvent::updateManipulatorsData() const{
    if(tButton_ == T_MOUSE_BUTTON::L)
        ManipulatorsContext::activeContext.isMouseLPressed_ = false;
    else
        ManipulatorsContext::activeContext.isMouseRPressed_ = false;
}

T_MOUSE_BUTTON MouseButtonReleasedEvent::tButton() const{ return tButton_; }
//____________________________________________________________________

MouseMovedEvent::MouseMovedEvent(Vector newPos, Vector oldPos):
    Event(T_EVENT::mouseMoved),
    newPos_(newPos), oldPos_(oldPos)
{}

void MouseMovedEvent::updateManipulatorsData() const{
    ManipulatorsContext::activeContext.mousePos_ = newPos_;
}

Vector MouseMovedEvent::newPos() const{ return newPos_; }
Vector MouseMovedEvent::oldPos() const{ return oldPos_; }
//____________________________________________________________________

MouseWheelScrolledEvent::MouseWheelScrolledEvent(int nTicks):
    Event(T_EVENT::mouseWheelScrolled),
    nTicks_(nTicks)
{}

void MouseWheelScrolledEvent::updateManipulatorsData() const{
    return;
}

int MouseWheelScrolledEvent::nTicks() const{ return nTicks_; }
//____________________________________________________________________

KeyPressedEvent::KeyPressedEvent(T_KEY key):
    Event(T_EVENT::keyPressed),
    key_(key)
{}

void KeyPressedEvent::updateManipulatorsData() const{
    ManipulatorsContext::activeContext.isKeyPressed_[static_cast<int>(key_)] = true;
}

T_KEY KeyPressedEvent::key() const{ return key_; }
//____________________________________________________________________

KeyReleasedEvent::KeyReleasedEvent(T_KEY key):
    Event(T_EVENT::keyReleased),
    key_(key)
{}

void KeyReleasedEvent::updateManipulatorsData() const{
    ManipulatorsContext::activeContext.isKeyPressed_[static_cast<int>(key_)] = false;
}

T_KEY KeyReleasedEvent::key() const{ return key_; }
//____________________________________________________________________

ManipulatorsContext ManipulatorsContext::activeContext;
