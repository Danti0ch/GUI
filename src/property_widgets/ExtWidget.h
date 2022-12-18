#ifndef EXTENDED_WIDGET_H
#define EXTENDED_WIDGET_H

#include "Widget.h"


template<class T_WIDGET, class... PROPERTIES>
class ExtWidget : virtual public T_WIDGET, virtual public PROPERTIES...{

public:
    ExtWidget(Vector size):
        Widget(size), PROPERTIES(this)...
    {}
    ~ExtWidget() = default;
};

#endif // EXTENDED_WIDGET_H
