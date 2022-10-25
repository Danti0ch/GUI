#ifndef BASIC_EVENTS_H
#define BASIC_EVENTS_H

#include "Event.h"

struct click_coord{
    uint x, y;
};
class MouseLClickEvent : public Event<click_coord>{
public:
    MouseLClickEvent():
        Event(){}

private:
    click_coord coord;
};

class KeyPressedEvent : public Event<KEY_TYPE>{
public:
    KeyPressedEvent():
        Event(T_CORE_EVENT::KEY_PRESSED){}

private:
    KEY_TYPE type;
};

#endif // BASIC_EVENTS_H
