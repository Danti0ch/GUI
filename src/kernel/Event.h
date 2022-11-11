#ifndef EVENT_H
#define EVENT_H

#include "stdlib.h"
enum class T_EVENT{
    unknown,
    mouseLClick,
    keyPressed,
    N_EVENTS
};

const int N_EVENTS = (int)T_EVENT::N_EVENTS;

class Widget;

class Event{
public:

    Event(T_EVENT id):
        id_(id){}

    virtual ~Event(){}

    T_EVENT id() const { return id_; }
    //int     id() const { return (int)id_; }

    /**
     * @brief проверяет действует ли событие на переданный виджет
     */
    virtual bool check(const Widget* widget) const = 0;
private:
    T_EVENT id_;
};

class MouseLClickEvent : public Event{
public:
    MouseLClickEvent(uint x, uint y):
        Event(T_EVENT::mouseLClick), x_(x), y_(y){}

    bool check(const Widget* widget) const override;

    uint x() const { return x_; }
    uint y() const { return y_; }

private: 
    uint x_, y_;
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

    bool check(const Widget* widget) const override;

    T_KEY key() const { return key_; }
private: 
    T_KEY key_;
};

#endif // EVENT_H
