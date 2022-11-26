#ifndef CANVAS_MANAGER_H
#define CANVAS_MANAGER_H

#include "CanvasWidget.h"
#include "ListWidget.h"
#include "Label.h"

// TODO: save implementing

// TODO: rename
struct CanvasStorage{
    std::string path;
    CanvasWidget* widget;
};
/*
class CanvasManager : public ContainerWidget{
public:
    CanvasManager(uint x, uint y);

private:
    HListWidget<CanvasManager> canvas_list_;
    std::list<CanvasStorage> storage_;
    Label default_text_;
};
*/
#endif // CANVAS_MANAGER_H
