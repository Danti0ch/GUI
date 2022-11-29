#ifndef DROP_LIST_H
#define DROP_LIST_H

#include "Widget.h"
#include "RectButton.h"
#include "ListWidget.h"

template<class T_RECEIVER>
class DropList : public ContainerWidget{
public:
    DropList(T_RECEIVER* p_receiver, uint controlButtWidth, uint controlButtHeight, uint listWidth, uint listHeight, uint listButHeight):
        ContainerWidget(std::max(controlButtWidth, listButWidth), std::max(controlButtHeight, listButHeight)),
        control_button_(controlButtWidth, controlButtHeight),
        list_(listWidth, listHeight, listButHeight, p_receiver, )
    ~DropList();

    void add(const std::string& name, )
private:
    RectButton<DropList, bool> control_button_;
    HListWidget<T_RECEIVER> list_;
private:
    void changeListVisibility();
};

#endif // DROP_LIST_H
