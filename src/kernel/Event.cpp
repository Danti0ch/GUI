#include "Event.h"

ManipulatorsContext::ManipulatorsContext():
    isKeyPressed_(N_KEYS, 0),
    isMouseLPressed_(false),
    isMouseRPressed_(false)
{}

ManipulatorsContext::~ManipulatorsContext(){}

bool ManipulatorsContext::isKeyPressed(T_KEY key) const { return static_cast<bool>(isKeyPressed_[static_cast<int>(key)]); }

bool ManipulatorsContext::isMouseLPressed() const { return isMouseLPressed; }
bool ManipulatorsContext::isMouseRPressed() const { return isMouseRPressed; }

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
        manipulatorsContext.isMouseLPressed_ = true;
    else
        manipulatorsContext.isMouseRPressed_ = true;
}

T_MOUSE_BUTTON MouseButtonPressedEvent::tButton() const{ return tButton_; }
//____________________________________________________________________

MouseButtonReleasedEvent::MouseButtonReleasedEvent(T_MOUSE_BUTTON tButton):
    Event(T_EVENT::mouseReleased),
    tButton_(tButton)
{}

void MouseButtonReleasedEvent::updateManipulatorsData() const{
    if(tButton_ == T_MOUSE_BUTTON::L)
        manipulatorsContext.isMouseLPressed_ = false;
    else
        manipulatorsContext.isMouseRPressed_ = false;
}

T_MOUSE_BUTTON MouseButtonReleasedEvent::tButton() const{ return tButton_; }
//____________________________________________________________________

MouseMovedEvent::MouseMovedEvent(Vector newPos):
    Event(T_EVENT::mouseMoved),
    newPos_(newPos)
{}

void MouseMovedEvent::updateManipulatorsData() const{
    manipulatorsContext.mousePos_ = newPos_;
}

Vector MouseMovedEvent::newPos() const{ return newPos_; }
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
    manipulatorsContext.isKeyPressed_[static_cast<int>(key_)] = true;
}

T_KEY KeyPressedEvent::key() const{ return key_; }
//____________________________________________________________________

KeyReleasedEvent::KeyReleasedEvent(T_KEY key):
    Event(T_EVENT::keyReleased),
    key_(key)
{}

void KeyPressedEvent::updateManipulatorsData() const{
    manipulatorsContext.isKeyPressed_[static_cast<int>(key_)] = false;
}

T_KEY KeyReleasedEvent::key() const{ return key_; }
//____________________________________________________________________
