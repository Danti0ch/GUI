#ifndef BASE_EVENTS_H
#define BASE_EVENTS_H
#include "Event.h"

class MouseLClickEvent : public Event{
public:
    MouseLClickEvent(uint x, uint y):
        Event(T_EVENT::mouseLClickEvent),
        x_(x),
        y_(y)
    {}

    bool check(const Widget* widget) const override;

    uint x() const { return x_; }
    uint y() const { return y_; }
private:
    uint x_, y_;
};

enum KEY_TYPE {
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
    KeyPressedEvent(KEY_TYPE type):
        Event(T_EVENT::keyPressedEvent),
        type_(type)
    {}

    bool check(const Widget* widget) const override;
    KEY_TYPE type() const { return type_; }
private:
    KEY_TYPE type_;
};

#endif // BASE_EVENTS_H
