
#include "ListWidget.h"

const uint SLIDER_SIZE = 20;

// TODO: copypaste 4 times, remove
typedef void (*T_HANDLER)();

// TODO:
template<typename T_ARG>
AbstractListWidget<T_ARG>::AbstractListWidget(uint x, uint y, uint width, uint height, uint elem_size):
    ExpendedContainerWidget(x, y, width, height, SLIDER_SIZE),
    elem_size_(elem_size),
    elems_()
{}

template<typename T_ARG>
void HListWidget<T_ARG>::add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg){
    
}
