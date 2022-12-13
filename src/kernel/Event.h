#ifndef SEVENT_H
#define SEVENT_H

// TODO: rename

#include "Auxil.h"
#include <vector>

enum class T_EVENT{
    unknown,
    mouseClick,
    mouseReleased,
    mouseMoved,
    mouseWheelScrolled,
    keyPressed,
    keyReleased
};

enum class T_KEY {
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
  BackSpace = Backspace, BackSlash = Backslash, SemiColon = Semicolon, Return = Enter,

  N_KEYS
};

const unsigned int N_KEYS = static_cast<unsigned int>(T_KEY::N_KEYS);

class ManipulatorsContext{
public:
    ManipulatorsContext();
    ~ManipulatorsContext();

    bool isKeyPressed(T_KEY key) const; 

    bool isMouseLPressed() const;
    bool isMouseRPressed() const;

    Vector mousePos() const;
private:
    std::vector<int> isKeyPressed_;

    bool isMouseLPressed_;
    bool isMouseRPressed_;

    Vector mousePos_;

friend class MouseButtonPressedEvent;
friend class MouseButtonReleasedEvent;
friend class MouseMovedEvent;
friend class MouseWheelScrolledEvent;
friend class KeyPressedEvent;
friend class KeyReleasedEvent;
};

class Event{
public:
    Event(T_EVENT type);
    ~Event();

    T_EVENT type() const;
protected:
    virtual void updateManipulatorsData() const = 0;
private:
    T_EVENT type_;
friend class Window;
};

enum class T_MOUSE_BUTTON{
    L, R
};

class MouseButtonPressedEvent : public Event{
public:
    MouseButtonPressedEvent(T_MOUSE_BUTTON tButton);

    T_MOUSE_BUTTON tButton() const;

private:
    void updateManipulatorsData() const override;
private:
    T_MOUSE_BUTTON tButton_;
};

class MouseButtonReleasedEvent : public Event{
public:
    MouseButtonReleasedEvent(T_MOUSE_BUTTON tButton);

    T_MOUSE_BUTTON tButton() const;
private:
    void updateManipulatorsData() const override;
private:
    T_MOUSE_BUTTON tButton_;
};

class MouseMovedEvent : public Event{
public:
    MouseMovedEvent(Vector newPos);

    Vector newPos() const;
private:
    void updateManipulatorsData() const override;
private:
    Vector newPos_;
};

class MouseWheelScrolledEvent : public Event{
public:
    MouseWheelScrolledEvent(int nTicks);

    int nTicks() const;
private:
    void updateManipulatorsData() const override;
private:
    int nTicks_;
};

class KeyPressedEvent : public Event{
public:
    KeyPressedEvent(T_KEY key);

    T_KEY key() const;
private:
    void updateManipulatorsData() const override;
private:
    T_KEY key_;
};

class KeyReleasedEvent : public Event{
public:
    KeyReleasedEvent(T_KEY key);

    T_KEY key() const;
private:
    void updateManipulatorsData() const override;
private:
    T_KEY key_;
};

ManipulatorsContext manipulatorsContext;

#endif // SEVENT_H
