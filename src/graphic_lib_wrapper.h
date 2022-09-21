#ifndef GL_WRAPPER
#define GL_WRAPPER

#define SFML_LIB 0
#define QT_LIB   1

#ifndef ACTIVE_GRAPHIC_LIB
#define ACTIVE_GRAPHIC_LIB SFML_LIB
#endif

//#if ACTIVE_GRAPHIC_LIB == SFML_LIB
    #include <SFML/Graphics.hpp>
    #include <SFML/Graphics/Vertex.hpp>


//#elif ACTIVE_GRAPHIC_LIB == QT_LIB
//    #include <QtWidgets>
//#endif
#include "geometry_objects.h"

namespace gglib{
enum Key {
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

// TODO: перегрузка + для даблов
class Color{
private:
    uint8_t r_, g_, b_, a_;
public:
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    Color(uint8_t r, uint8_t g, uint8_t b);
    
    uint8_t r() const { return r_; }
    uint8_t g() const { return g_; }
    uint8_t b() const { return b_; }
    uint8_t a() const { return a_; }

    void    r(uint8_t v) { r_ = v; }
    void    g(uint8_t v) { g_ = v; }
    void    b(uint8_t v) { b_ = v; }
    void    a(uint8_t v) { a_ = v; }

    //operator double() const;

    void  operator +=(const Color& col2);
    void  operator *=(const Color& col2);
    void  operator *=(double ratio);
    void  operator -=(const Color& col2);

    Color operator +(const Color& col2) const;
    Color operator *(const Color& col2) const;
    Color operator *(double ratio) const;
    Color operator -(const Color& col2) const;
};
//----------------------------------------------------------------------------------------//

class GraphicSpace{

private:

//#if ACTIVE_GRAPHIC_LIB == SFML_LIB
    sf::RenderWindow window_;
//#elif ACTIVE_GRAPHIC_LIB == QT_LIB
//    QWidget wgt;    
//#endif

public:
    GraphicSpace(uint x_pixels, uint y_pixels);

    virtual void MouseButtonPressHandler(uint x_pos, uint y_pos){}
    virtual void CloseButtonPressHandler(){}
    virtual void KeyPressHandler(Key key){}
    virtual void Update(){}
    virtual void UpdateAfterEvents(){}
    
    void Show();
    void Close();
    void Clear(Color col = Color(255, 255, 255, 255));
    void Init();

    void DrawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, Color col = Color(0, 0, 0, 255));
    void DrawPixel(uint x_pix, uint y_pix, Color col = Color(0, 0, 0, 255));

    uint sizeX() const { return window_.getSize().x; }
    uint sizeY() const { return window_.getSize().y; }
};
//----------------------------------------------------------------------------------------//

class CoordinateSus{

private:
    
    double x_lower_lim_, x_upper_lim_;
    double y_lower_lim_, y_upper_lim_;

    int x_lower_pixel_, x_upper_pixel_;
    int y_lower_pixel_, y_upper_pixel_;

    int n_x_upper_axis_pixels_, n_x_lower_axis_pixels_;
    int n_y_upper_axis_pixels_, n_y_lower_axis_pixels_;
    
    double scale_x_, scale_y_;
    double step_val_;
public:
    
    CoordinateSus(uint x_lower_pixel, uint x_upper_pixel, uint y_upper_pixel, uint y_lower_pixel,
                  double x_lower_lim, double x_upper_lim, double y_lower_lim, double y_upper_lim);

    double x_lower_lim() const { return x_lower_lim_; }
    double x_upper_lim() const { return x_upper_lim_; }
    double y_lower_lim() const { return y_lower_lim_; }
    double y_upper_lim() const { return y_upper_lim_; }
    
    int x_lower_pixel() const { return x_lower_pixel_; }
    int x_upper_pixel() const { return x_upper_pixel_; }
    int y_lower_pixel() const { return y_lower_pixel_; }
    int y_upper_pixel() const { return y_upper_pixel_; }
    
    double scale_x()  const { return scale_x_; }
    double scale_y()  const { return scale_y_; }
    double step_val() const { return step_val_; }
    
    int CountPixelPosX(double x_ct) const;
    int CountPixelPosY(double y_ct) const;

    double CountAxisPosX(int x_pixel) const;
    double CountAxisPosY(int y_pixel) const;

    void Draw(GraphicSpace* editor, Color col = Color(255, 255, 255, 255), Color axis_col = Color(0, 0, 255, 255)) const;
    ~CoordinateSus(){}
};

int CheckCoordInCTS(const CoordinateSus& cts, uint x, uint y);
//----------------------------------------------------------------------------------------//

typedef geom::VT_DATA VT_DATA;
// TODO: -> inheritance?
class Vector : public geom::Vector{

private:
    Color col_;

public:

    Vector();
    Vector(const geom::Vector& vt);
    Vector(double v1, double v2, VT_DATA mod);
    Vector(double v1, double v2, VT_DATA mod, Color col);
    
    void Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, Color col = Color(255, 0, 0));
    void Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, double x_init, double y_init, Color col = Color(255, 0, 0));
    void Draw(GraphicSpace* editor, const CoordinateSus& ct_sus, const Vector& vt_init, Color col = Color(255, 0, 0));
};
//----------------------------------------------------------------------------------------//

class Button{

private:
    uint x_upper_pix_, x_lower_pix_;
    uint y_upper_pix_, y_lower_pix_;

    Color col_;

public:

    Button(uint x_lower_pix, uint y_upper_pix, uint x_upper_pix, uint y_lower_pix, Color col);

    uint x_lower_pix() const { return x_lower_pix_; }
    uint x_upper_pix() const { return x_upper_pix_; }
    uint y_lower_pix() const { return y_lower_pix_; }
    uint y_upper_pix() const { return y_upper_pix_; }

    Color col() const { return col_; }
    void Draw(GraphicSpace* editor);
};

int  CheckCoordInButton(const Button& but, uint x, uint y);

//----------------------------------------------------------------------------------------//

} // gglib
#endif // GL_WRAPPER
