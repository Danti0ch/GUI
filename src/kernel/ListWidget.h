#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include "Widget.h"
#include "Buttons.h"
#include "Slider.h"
#include "Expended.h"

//? should it support not specific type widgets

//!!!!!!!!!!!!!! MAKE THAT IT WOULD NOT HAVE T_ARG, BUT RETURN  TO BUTTON HANDLER ID OF THE PRESSED ITEM

class AbstractListWidget : public Expended{
public:

    AbstractListWidget(Vector size, coord itemLen);
    ~AbstractListWidget();

    void add(ORIENTATION orient, const std::string& name);
    void add(ORIENTATION orient, const std::string& name, Action* action);

    std::vector<RectButton*>& items();
    void setHandler(const std::string& name, Action* action);
protected:
    std::vector<RectButton*> items_;
    coord itemLen_;
};

class HListWidget : public AbstractListWidget{
public:
    HListWidget(Vector size);
    HListWidget(Vector size, coord itemLen);

    ~HListWidget() = default;

    void add(const std::string& name);
    void add(const std::string& name, Action* action);

    static coord DEFAULT_ITEM_SIZE;
};

class VListWidget : public AbstractListWidget{
public:
    VListWidget(Vector size);
    VListWidget(Vector size, coord itemLen);

    ~VListWidget() = default;

    void add(const std::string& name);
    void add(const std::string& name, Action* action);

    static coord DEFAULT_ITEM_SIZE;
};

#endif // LIST_WIDGET_H
