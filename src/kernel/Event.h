#ifndef EVENT_H
#define EVENT_H

//? maybe remove the inheritance mechanic and make general class for all event

#include "stdlib.h"
enum class T_EVENT{
    unknown,
    mouseLClick,
    mouseMoved,
    mouseReleased,
    keyPressed,
    sliderMoved
};

class Widget;

class Event{
public:

    Event(T_EVENT type):
        type_(type){}

    virtual ~Event(){}

    // TODO: rename to type
    T_EVENT type() const { return type_; }
    //int     id() const { return (int)id_; }

    /**
     * @brief проверяет действует ли событие на переданный виджет
     */
    //virtual bool check(const Widget* widget) const = 0;
private:
    T_EVENT type_;
};

class MouseEvent : public Event{
public:
    MouseEvent(T_EVENT type, uint x, uint y):
        Event(type), x_(x), y_(y){}

    //bool check(const Widget* widget) const override;

    uint x() const { return x_; }
    uint y() const { return y_; }
private:
    uint x_;
    uint y_;
};

class MouseLClickEvent : public MouseEvent{
public:
    MouseLClickEvent(uint x, uint y):
        MouseEvent(T_EVENT::mouseLClick, x, y){}
};

class MouseMovedEvent : public MouseEvent{
public:
    MouseMovedEvent(uint x, uint y):
        MouseEvent(T_EVENT::mouseMoved, x, y){}
};

class MouseReleasedEvent : public MouseEvent{
public:
    MouseReleasedEvent(uint x, uint y):
        MouseEvent(T_EVENT::mouseReleased, x, y){}
};

enum T_KEY {
    Unknown = -1, A = 0, B, C,
    D, E, F, G,
    H, I, J, K,
    L, M, N, O,
    P, Q, R, S,
    T, U, V, W,
    X, Y, Z, Num0,
    Num1, Num2, Num3, Num4,
    Num5, Num6, Num7, Num8,
    Num9, Escape, LControl, LShift,
    LAlt, LSystem, RControl, RShift,
    RAlt, RSystem, Menu, LBracket,
    RBracket, Semicolon, Comma, Period,
    Quote, Slash, Backslash, Tilde,
    Equal, Hyphen, Space, Enter,
    Backspace, Tab, PageUp, PageDown,
    End, Home, Insert, Delete,
    Add, Subtract, Multiply, Divide,
    Left, Right, Up, Down,
    Numpad0, Numpad1, Numpad2, Numpad3,
    Numpad4, Numpad5, Numpad6, Numpad7,
    Numpad8, Numpad9, F1, F2,
    F3, F4, F5, F6,
    F7, F8, F9, F10,
    F11, F12, F13, F14,
    F15, Pause, KeyCount, Dash = Hyphen,
  BackSpace = Backspace, BackSlash = Backslash, SemiColon = Semicolon, Return = Enter
};
class KeyPressedEvent : public Event{
public:
    KeyPressedEvent(T_KEY key):
        Event(T_EVENT::keyPressed), key_(key){}

    //bool check(const Widget* widget) const override;

    T_KEY key() const { return key_; }
private: 
    T_KEY key_;
};

//? should slider know what widgets are connected to it to distrubute event
class SliderMovedEvent : public Event{
public:
    // TODO: fix Widget* -> AbstractSlider*
    SliderMovedEvent(Widget* p_slider, double ratio):
        Event(T_EVENT::sliderMoved), p_slider_(p_slider), ratio_(ratio){}
    
    //bool check(const Widget* widget) const override;

    const Widget* p_slider() const { return p_slider_; }
    double ratio() const { return ratio_; }

private:
    Widget* p_slider_;
    double ratio_;
};

#endif // EVENT_H
