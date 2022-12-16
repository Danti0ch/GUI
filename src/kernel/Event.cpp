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

#define CHECK_LETTER(t_key, val)        \
    if(key == t_key){             \
        if(context.isKeyPressed(T_KEY::LControl)){   \
            return val + 'A' - 'a';        \
        }                                   \
        return val;                          \
    }

#define CHECK_NON_LETTER(t_key, val) \
    if(key == t_key){ \
        return val; \
    }

char convertKeyToChar(T_KEY key, const ManipulatorsContext& context){

    char symb = 0;

    CHECK_LETTER(T_KEY::Q, 'q');
    CHECK_LETTER(T_KEY::W, 'w');
    CHECK_LETTER(T_KEY::E, 'e');
    CHECK_LETTER(T_KEY::R, 'r');
    CHECK_LETTER(T_KEY::T, 't');
    CHECK_LETTER(T_KEY::Y, 'y');
    CHECK_LETTER(T_KEY::U, 'u');
    CHECK_LETTER(T_KEY::I, 'i');
    CHECK_LETTER(T_KEY::O, 'o');
    CHECK_LETTER(T_KEY::P, 'p');
    CHECK_LETTER(T_KEY::A, 'a');
    CHECK_LETTER(T_KEY::S, 's');
    CHECK_LETTER(T_KEY::D, 'd');
    CHECK_LETTER(T_KEY::F, 'f');
    CHECK_LETTER(T_KEY::G, 'g');
    CHECK_LETTER(T_KEY::H, 'h');
    CHECK_LETTER(T_KEY::J, 'j');
    CHECK_LETTER(T_KEY::K, 'k');
    CHECK_LETTER(T_KEY::L, 'l');
    CHECK_LETTER(T_KEY::Z, 'z');
    CHECK_LETTER(T_KEY::X, 'x');
    CHECK_LETTER(T_KEY::C, 'c');
    CHECK_LETTER(T_KEY::V, 'v');
    CHECK_LETTER(T_KEY::B, 'b');
    CHECK_LETTER(T_KEY::N, 'n');
    CHECK_LETTER(T_KEY::M, 'm');

    CHECK_NON_LETTER(T_KEY::Num0, '0');
    CHECK_NON_LETTER(T_KEY::Num1, '1');
    CHECK_NON_LETTER(T_KEY::Num2, '2');
    CHECK_NON_LETTER(T_KEY::Num3, '3');
    CHECK_NON_LETTER(T_KEY::Num4, '4');
    CHECK_NON_LETTER(T_KEY::Num5, '5');
    CHECK_NON_LETTER(T_KEY::Num6, '6');
    CHECK_NON_LETTER(T_KEY::Num7, '7');
    CHECK_NON_LETTER(T_KEY::Num8, '8');
    CHECK_NON_LETTER(T_KEY::Num9, '9');

    CHECK_NON_LETTER(T_KEY::Numpad0, '0');
    CHECK_NON_LETTER(T_KEY::Numpad1, '1');
    CHECK_NON_LETTER(T_KEY::Numpad2, '2');
    CHECK_NON_LETTER(T_KEY::Numpad3, '3');
    CHECK_NON_LETTER(T_KEY::Numpad4, '4');
    CHECK_NON_LETTER(T_KEY::Numpad5, '5');
    CHECK_NON_LETTER(T_KEY::Numpad6, '6');
    CHECK_NON_LETTER(T_KEY::Numpad7, '7');
    CHECK_NON_LETTER(T_KEY::Numpad8, '8');
    CHECK_NON_LETTER(T_KEY::Numpad9, '9');

    CHECK_NON_LETTER(T_KEY::LBracket, '[');
    CHECK_NON_LETTER(T_KEY::RBracket, ']');
    CHECK_NON_LETTER(T_KEY::Semicolon, ';');
    CHECK_NON_LETTER(T_KEY::Comma, ',');
    CHECK_NON_LETTER(T_KEY::Period, '.');
    CHECK_NON_LETTER(T_KEY::Quote, '\'');
    CHECK_NON_LETTER(T_KEY::Slash, '/');
    CHECK_NON_LETTER(T_KEY::BackSlash, '\\');
    CHECK_NON_LETTER(T_KEY::Tilde, '~');
    CHECK_NON_LETTER(T_KEY::Equal, '=');
    CHECK_NON_LETTER(T_KEY::Hyphen, '-');
    CHECK_NON_LETTER(T_KEY::Space, ' ');
    CHECK_NON_LETTER(T_KEY::Enter, '\n');
    CHECK_NON_LETTER(T_KEY::Tab, '\t');
    CHECK_NON_LETTER(T_KEY::Add, '+');
    CHECK_NON_LETTER(T_KEY::Multiply, '*');
    CHECK_NON_LETTER(T_KEY::Divide, '/');

    return 0;
}
