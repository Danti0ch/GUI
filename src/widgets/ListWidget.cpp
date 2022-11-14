
#include "ListWidget.h"

/*
const uint SLIDER_SIZE = 20;

// TODO: figure out: error: there are no arguments to ‘height’ that depend on a template parameter, so a declaration of ‘height’ must be avai
// TODO: copypaste 4 times, remove
typedef void (*T_HANDLER)();

// TODO: refactor copypaste
// TODO:
template<typename T_ARG>
AbstractListWidget<T_ARG>::AbstractListWidget(uint x, uint y, uint width, uint height, uint elem_size):
    ExpendedContainerWidget(x, y, width, height, SLIDER_SIZE),
    elem_size_(elem_size),
    elems_()
{}


template<typename T_ARG>
HListWidget<T_ARG>::HListWidget(uint x, uint y, uint width, uint height, uint elem_width):
    AbstractListWidget<T_ARG>(x, y, width, height, elem_width){}

template<typename T_ARG>
void HListWidget<T_ARG>::add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg){

    // TODO: remove this->??
    this->elems_.push_back(RectButton<T_ARG>(this->elems_.size() * this->elem_size_ + this->x(), this->y(), this->elem_size_, this->height()));

    this->elems_[this->elems_.size() - 1].data(arg);
    this->elems_[this->elems_.size() - 1].handler(p_handler);
    this->elems_[this->elems_.size() - 1].setText(label);

    ExpendedContainerWidget::connect(&(this->elems_[this->elems_.size() - 1]));
    return;
}

template<typename T_ARG>
VListWidget<T_ARG>::VListWidget(uint x, uint y, uint width, uint height, uint elem_width):
    AbstractListWidget<T_ARG>(x, y, width, height, elem_width){}

template<typename T_ARG>
void VListWidget<T_ARG>::add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg){

    this->elems_.push_back(RectButton<T_ARG>(this->x(), this->elems_.size() * this->elem_size_ + this->y(), this->width(), this->elem_height_));

    this->elems_[this->elems_.size() - 1].data(arg);
    this->elems_[this->elems_.size() - 1].handler(p_handler);
    this->elems_[this->elems_.size() - 1].setText(label);

    ExpendedContainerWidget::connect(&(this->elems_[this->elems_.size() - 1]));
    return;
}
*/
