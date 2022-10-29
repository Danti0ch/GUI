#ifndef EVENT_H
#define EVENT_H

class Widget;
enum class T_EVENT{
    unknown,
    mouseLClickEvent,
    keyPressedEvent,
    N_EVENTS
};

const int N_EVENTS = (int)T_EVENT::N_EVENTS;

class Widget;

class Event{
public:

    Event(T_EVENT id):
        id_(id){}

    virtual ~Event(){}

    //T_EVENT id() const { return id_; }
    int     id() const { return (int)id_; }

    /**
     * @brief проверяет действует ли событие на переданный виджет
     */
    virtual bool check(const Widget* widget) const = 0;
private:
    T_EVENT id_;
};

#endif // EVENT_H
