#ifndef GL_WRAPPER
#define GL_WRAPPER

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

class Color{
private:
    uint r_, g_, b_, a_;
public:
    Color(uint r, uint g, uint b, uint a):
        r_(r), g_(g), b_(b), a_(a){}
    Color(uint r, uint g, uint b):
        r_(r), g_(g), b_(b), a_(255){}
    
    uint r() const { return r_; }
    uint g() const { return g_; }
    uint b() const { return b_; }
    uint a() const { return a_; }
};

class myButton{

private:
    uint x_upper_pix_, x_lower_pix_;
    uint y_upper_pix_, y_lower_pix_;

    Color col_;

public:

    myButton(uint x_lower_pix, uint y_upper_pix, uint x_upper_pix, uint y_lower_pix, Color col);

    uint x_lower_pix() const { return x_lower_pix_; }
    uint x_upper_pix() const { return x_upper_pix_; }
    uint y_lower_pix() const { return y_lower_pix_; }
    uint y_upper_pix() const { return y_upper_pix_; }

    Color col() const { return col_; }
};

int  CheckCoordInButton(const myButton& but, uint x, uint y);

// TODO: скорость попиксельной отрисовки будет низкой
class GraphicSpace{

private:

    sf::RenderWindow window_;
    // TODO: обьединить в класс, массив?
    void (*mouse_button_press_handler_)(GraphicSpace* obj, int x_pos, int y_pos);
    void (*close_button_press_handler_)(GraphicSpace* obj);

    void (*update_)(GraphicSpace* obj);
public:
    GraphicSpace(uint x_pixels, uint y_pixels);

    void Show();
    void Close();
    void Clear(Color col = Color(255, 255, 255, 255));

    void HandleEvents();

    void DrawLine(uint x_pix1, uint y_pix1, uint x_pix2, uint y_pix2, Color col = Color(0, 0, 0, 255));
    void DrawPixel(uint x_pix, uint y_pix, Color col = Color(0, 0, 0, 255));

    void MouseButtonPressHandler(x_pos, y_pos);
    void CloseButtonPressHandler();
    void Update();
    
    void SetMouseButtonPressEvent(void (*func)(GraphicSpace* obj, int x_pos, int y_pos));
    void SetCloseButtonPressEvent(void (*func)(GraphicSpace* obj));
    void SetUpdateHandler(void (*func)(GraphicSpace* obj));

    uint sizeX() const { return window_.getSize().x; }
    uint sizeY() const { return window_.getSize().y; }
    
    void Draw(const myButton& butt);
    ~GraphicSpace();
};

#endif // GL_WRAPPER

// TODO: функция process events, wrapper для событий
