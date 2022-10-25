#ifndef GRAPHIC_SPACE_KERNEL_ABSTRACT_H
#define GRAPHIC_SPACE_KERNEL_ABSTRACT_H

#include "Pixel.h"

enum class T_CORE_EVENT{
    UNDEFINED,
    MOUSE_L_CLICK,
    KEY_PRESSED,
};

// TODO: refactor
uint N_CORE_EVENTS = 3;

class CoreEvent{

public:
    CoreEvent(T_CORE_EVENT type){ id_ = id; }
    ~CoreEvent(){}

    uint id() const { return (uint)id_; }

    virtual bool check(const Widget* widget) const = 0;
private:
    KEY_TYPE id_;
};

// TODO: можно перебросить в подклассы одного класса
class MouseLClickCoreEvent : public CoreEvent{

public:
    MouseLClickCoreEvent(uint x, uint y):
        CoreEvent(T_CORE_EVENT::MOUSE_L_CLICK), x_(x), y_(y) {}

    bool check(const Widget* widget) const override{
        if(widget->x() <= x_ && widget->x() + widget->width()  >= x_ && 
           widget->y() <= y_ && widget->y() + widget->height() >= y_){
                return true;
           }
        return false;
    }

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

class KeyPressedCoreEvent : public CoreEvent{

public:
    KeyPressedCoreEvent(KEY_TYPE type):
        CoreEvent(T_CORE_EVENT::KEY_PRESSED), type_(type) {}

    bool check(const Widget* widget) const override{
        if(widget->focused()) return true;
        return false;
    }
    
private:
    KEY_TYPE type_;  
};

class GraphicSpaceKernelAbstract{

public:
    GraphicSpaceKernelAbstract(uint width, uint height):
        width_(width), height_(height) {}

    virtual void  drawText(uint x_pixel, uint y_pixel, const std::string& str, uint font_size, Color col) = 0;
    virtual void  drawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, Color col) = 0;
    virtual void  drawPixel(uint x_pix, uint y_pix, Color col) = 0;
    virtual void  drawPixels(const std::vector<Pixel>& pixs_to_draw) = 0;
    virtual void  clear(Color col) = 0;
    virtual void  show() = 0;
    virtual void  close() = 0;
    virtual bool  isopen() = 0;
//    virtual Matrix<Color> GetPixsFromFile(const std::string& filename) const = 0;
    virtual bool extractEvent(CoreEvent* core_event) = 0;

    constexpr uint width() const { return width_; }
    constexpr uint height() const { return height_; }

private:
    uint width_, height_;
};

#endif // GRAPHIC_SPACE_KERNEL_ABSTRACT_H