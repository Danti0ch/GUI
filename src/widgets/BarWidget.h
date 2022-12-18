#ifndef BAR_WIDGET_H
#define BAR_WIDGET_H

#include "Widget.h"
#include "ListWidget.h"

class BarWidget : public ContainerWidget{
public:
    BarWidget(Vector size);
    ~BarWidget();

    // TODO: fix that multiple types of widgets available
    virtual void add(const std::string& label, Widget* widget) = 0;

protected:
    virtual Vector countDroppedPos(uint nDropped) = 0;
    void setDropped(uint nWidget);
protected:
    std::list<Widget*> droppedWidgets_;
    Widget* activeDropped_;
};

class hBarWidget : public BarWidget{
public:
    hBarWidget(Vector size, bool isTop, coord listSize = 20 );
    ~hBarWidget() ;

    void add(const std::string& label, Widget* widget) override;
private:
    Vector countDroppedPos(uint nDropped) override;

private:
    // TODO: move to base class
    HListWidget* list_;
    bool isTop_;
};

class vBarWidget : public BarWidget{
public:
    vBarWidget(Vector size, bool isRight, coord listSize = 20);
    ~vBarWidget(); 

    void add(const std::string& label, Widget* widget) override;
private:
    Vector countDroppedPos(uint nDropped) override;
private:
    VListWidget* list_;

    bool isRight_;
};

#endif // BAR_WIDGET_H
