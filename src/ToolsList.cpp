#include "ToolsList.h"

//? should i make version that non-depended on class type?

ToolsList::ToolsList():
    ContainerWidget(350, 560),
    list_(150, 560, 30, this, &ToolsList::setActiveTool),
    manager_(),
    setupWidgets_()
{   
    connect(&list_, 0, 0);

    manager_.updateTools();

    const std::list<ToolWrapper> tools = manager_.tools();
    std::list<ToolWrapper>::const_iterator tools_iter;

    texture().setTransparency(0);

    for (tools_iter = tools.begin(); tools_iter != tools.end(); tools_iter++){
        list_.add(tools_iter->name);

        SetupWidget* setupWidget = new SetupWidget(&manager_);

        setupWidget->setVisible(false);
        setupWidgets_.push_back(setupWidget);

        ToolManager::ACTIVE_SETUP_WINDOW = setupWidget;
        tools_iter->p->buildSetupWidget();
        connect(setupWidget, &list_, LINKAGE_MODE::RIGHT);
    }
}

ToolsList::~ToolsList(){
    std::list<SetupWidget*>::iterator iter;
    for (iter = setupWidgets_.begin(); iter != setupWidgets_.end(); iter++){
        delete *iter;
    }

    return;
}

ToolManager* ToolsList::toolManager(){
    return &manager_;
}

void ToolsList::setActiveTool(uint n_tool){
    
    std::list<SetupWidget*>::iterator setupWidgetIter = setupWidgets_.begin();
    std::advance(setupWidgetIter, n_tool);

    if(manager_.getNActiveTool() == n_tool){
        (*setupWidgetIter)->setVisible(!((*setupWidgetIter)->isVisible()));
        return;
    }
    
    const Widget* tool_item = list_.elems()[n_tool];

    uint y_pos = tool_item->y();
    uint x_pos = list_.width();

    if(tool_item->x() + (*setupWidgetIter)->height() > height()){
        y_pos = height() - (*setupWidgetIter)->height();
    }

    (*setupWidgetIter)->x(x_pos);
    (*setupWidgetIter)->y(y_pos);
    
    if(manager_.getActiveTool() != NULL){
        std::list<SetupWidget*>::iterator curActiveSetupWidget = setupWidgets_.begin();
        std::advance(curActiveSetupWidget, manager_.getNActiveTool());

        (*curActiveSetupWidget)->setVisible(false);
    }

    (*setupWidgetIter)->setVisible(true);

    ToolManager::ACTIVE_SETUP_WINDOW = (*setupWidgetIter);

    manager_.setActiveTool(n_tool);

    return;
}

void ToolsList::onSliderMoved(const SliderMovedEvent* event){

    if(event->p_slider() == list_.pHSlider() && manager_.getActiveTool() != NULL){

        std::list<SetupWidget*>::iterator setupWidgetIter = setupWidgets_.begin();
        std::advance(setupWidgetIter, manager_.getNActiveTool());

        (*setupWidgetIter)->setVisible(false);
    }

    return;
}

void ToolsList::draw(){

    std::list<Widget*>::iterator subwidgets_iter;
    for (subwidgets_iter = subwidgets_.begin(); subwidgets_iter != subwidgets_.end(); subwidgets_iter++){
        if((*subwidgets_iter)->isVisible()){
            
            (*subwidgets_iter)->coreDraw();
            GetPointerOnPixBuff()->drawPixelBuffer((*subwidgets_iter)->x(), (*subwidgets_iter)->y(), (*subwidgets_iter)->pixBuff());
        }
    }

    return;
}
