#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include "Widget.h"
#include "RectButton.h"
#include "Slider.h"
#include "ExpendedContainerWidget.h"

//? should it support not specific type widgets
//? T_ARG remove

const uint SLIDER_SIZE = 6;

//!!!!!!!!!!!!!! MAKE THAT IT WOULD NOT HAVE T_ARG, BUT RETURN  TO BUTTON HANDLER ID OF THE PRESSED ITEM

// TODO: figure out: error: there are no arguments to ‘height’ that depend on a template parameter, so a declaration of ‘height’ must be avai
// TODO: copypaste 4 times, remove

// TODO: refactor copypaste
// TODO:

// TODO: add remove

template<class T_DISTR>
class AbstractListWidget : public ExpendedContainerWidget{
public:
    typedef void (T_DISTR::*T_HANDLER)(uint);

    AbstractListWidget(uint width, uint height, uint elem_size, T_DISTR* p_distr, const T_HANDLER p_handler):
        ExpendedContainerWidget(width, height, SLIDER_SIZE),
        elem_size_(elem_size),
        elems_(),
        p_distr_(p_distr),
        handler_(p_handler)
    {}

    //? ok
    //void connect(Widget* child_widget) = delete;
    //void remove( Widget* child_widget) = delete;
    
    const std::vector<RectButton<T_DISTR, uint>*>& elems(){
        return elems_;
    }

    uint elem_size() const { return elem_size_; }
protected:
    std::vector<RectButton<T_DISTR, uint>*> elems_;
protected:
    uint elem_size_;
    T_HANDLER handler_;
    T_DISTR*  p_distr_;
};

template<class T_DISTR>
class HListWidget : public AbstractListWidget<T_DISTR>{
public:
    typedef void (T_DISTR::*T_HANDLER)(uint);

    HListWidget(uint width, uint height, uint elem_width, T_DISTR* p_distr, const T_HANDLER p_handler):
        AbstractListWidget<T_DISTR>(width, height, elem_width, p_distr, p_handler){}

    void add(const std::string& label){
        // TODO: remove this->??

        // TODO:
        this->elems_.push_back(new RectButton<T_DISTR, uint>(this->elem_size(), this->height()));

        this->elems_[this->elems_.size() - 1]->data(this->elems_.size() - 1);    
        this->elems_[this->elems_.size() - 1]->handler(this->p_distr_, this->handler_);
        this->elems_[this->elems_.size() - 1]->setText(label);
        this->elems_[this->elems_.size() - 1]->setTexture(Color(255, 255, 255));
        this->elems_[this->elems_.size() - 1]->setHoverTexture(Color(204, 204, 255));

        ExpendedContainerWidget::connect(this->elems_[this->elems_.size() - 1], (this->elems_.size() - 1) * this->elem_size(), 0);
        return;
    }
};

// TODO: make adding widget from top to bottom
template<class T_DISTR>
class VListWidget : public AbstractListWidget<T_DISTR>{
public:
    typedef void (T_DISTR::*T_HANDLER)(uint);

    VListWidget(uint width, uint height, uint elem_height, T_DISTR* p_distr, const T_HANDLER p_handler):
        AbstractListWidget<T_DISTR>(width, height, elem_height, p_distr, p_handler){}

    void add(const std::string& label){
        this->elems_.push_back(new RectButton<T_DISTR, uint>(this->width(), this->elem_size()));

        this->elems_[this->elems_.size() - 1]->data(this->elems_.size() - 1);
        this->elems_[this->elems_.size() - 1]->handler(this->p_distr_, this->handler_);
        this->elems_[this->elems_.size() - 1]->setText(label);
        this->elems_[this->elems_.size() - 1]->setTexture(Color(255, 255, 255));
        this->elems_[this->elems_.size() - 1]->setHoverTexture(Color(204, 204, 255));

        ExpendedContainerWidget::connect(this->elems_[this->elems_.size() - 1], 0, (this->elems_.size() - 1) * this->elem_size());
        return;
    }
};

#endif // LIST_WIDGET_H
