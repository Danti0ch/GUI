#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include "Widget.h"
#include "RectButton.h"
#include "Slider.h"
#include "ExpendedContainerWidget.h"

//? should it support not specific type widgets
//? T_ARG remove


const uint SLIDER_SIZE = 20;

// TODO: figure out: error: there are no arguments to ‘height’ that depend on a template parameter, so a declaration of ‘height’ must be avai
// TODO: copypaste 4 times, remove

// TODO: refactor copypaste
// TODO:

// TODO: add remove
template<typename T_ARG>
class AbstractListWidget : public ExpendedContainerWidget{
public:
    typedef void (*T_HANDLER)();

    AbstractListWidget(uint x, uint y, uint width, uint height, uint elem_size):
        ExpendedContainerWidget(x, y, width, height, SLIDER_SIZE),
        elem_size_(elem_size),
        elems_()
    {}

    //? ok
    //void connect(Widget* child_widget) = delete;
    //void remove( Widget* child_widget) = delete;
    
    uint elem_size() const { return elem_size_; }
protected:
    std::vector<RectButton<T_ARG>*> elems_;
private:
    uint elem_size_;
};

template<typename T_ARG>
class HListWidget : public AbstractListWidget<T_ARG>{
public:
    typedef void (*T_HANDLER)(T_ARG arg);

    HListWidget(uint x, uint y, uint width, uint height, uint elem_width):
        AbstractListWidget<T_ARG>(x, y, width, height, elem_width){}

    void add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg){
        // TODO: remove this->??
        // TODO:
        this->elems_.push_back(new RectButton<T_ARG>(this->elems_.size() * this->elem_size(), 0, this->elem_size(), this->height()));

        this->elems_[this->elems_.size() - 1]->data(arg);
        this->elems_[this->elems_.size() - 1]->handler(p_handler);
        this->elems_[this->elems_.size() - 1]->setText(label);
        this->elems_[this->elems_.size() - 1]->setTexture(Color(255, 255, 255));
        
        ExpendedContainerWidget::connect(this->elems_[this->elems_.size() - 1]);
        return;
    }
};

template<typename T_ARG>
class VListWidget : public AbstractListWidget<T_ARG>{
public:
    typedef void (*T_HANDLER)(T_ARG arg);

    VListWidget(uint x, uint y, uint width, uint height, uint elem_height):
        AbstractListWidget<T_ARG>(x, y, width, height, elem_height){}

    void add(const std::string& label, T_HANDLER p_handler, const T_ARG& arg){
        this->elems_.push_back(new RectButton<T_ARG>(0, this->elems_.size() * this->elem_size_, this->width(), this->elem_height_));

        this->elems_[this->elems_.size() - 1]->data(arg);
        this->elems_[this->elems_.size() - 1]->handler(p_handler);
        this->elems_[this->elems_.size() - 1]->setText(label);
        this->elems_[this->elems_.size() - 1]->setTexture(Color(255, 255, 255));

        ExpendedContainerWidget::connect(this->elems_[this->elems_.size() - 1]);
        return;
    }
};


#endif // LIST_WIDGET_H
