#include "ToolsList.h"

//? should i make version that non-depended on class type?

ToolsList::ToolsList():
    ContainerWidget({350, 560}),
    list_(new VListWidget({80, 560}, 80)),
    manager_(new ToolManager()),
    setupWidgets_()
{   
    list_->setVMoveHandler<ToolsList>(this, &ToolsList::ScrolledSlot);
    connect(list_, {0, 0});

    manager_->updateTools();

    const std::list<ToolWrapper> tools = manager_->tools();
    std::list<ToolWrapper>::const_iterator tools_iter;

    bgLayer_->transparency(0);

    uint n_tool = 0;

    for (tools_iter = tools.begin(); tools_iter != tools.end(); tools_iter++){
        list_->add(tools_iter->name, new ObjArgAction<ToolsList, uint>(this, &ToolsList::setActiveTool, n_tool));

        SetupWidget* setupWidget = new SetupWidget(manager_);

        setupWidget->visible(false);
        setupWidgets_.push_back(setupWidget);

        SetupWidget::ACTIVE_SETUP_WINDOW = setupWidget;
        tools_iter->p->buildSetupWidget();

        setupWidget->connectBy(list_, LINKAGE_MODE::RIGHT);
        n_tool++;
    }
}

ToolsList::~ToolsList(){
    std::list<SetupWidget*>::iterator iter;
    for (iter = setupWidgets_.begin(); iter != setupWidgets_.end(); iter++){
        delete *iter;
    }

    delete list_;
    delete manager_;
}

ToolManager* ToolsList::toolManager(){
    return manager_;
}

void ToolsList::setActiveTool(uint n_tool){
    
    std::list<SetupWidget*>::iterator setupWidgetIter = setupWidgets_.begin();
    std::advance(setupWidgetIter, n_tool);

    if(manager_->getNActiveTool() == n_tool){
        (*setupWidgetIter)->visible(!((*setupWidgetIter)->isVisible()));
        return;
    }
    
    const Widget* tool_item = list_->items()[n_tool];

    Vector pos(list_->size().x, tool_item->pos().y);

    if(tool_item->pos().y + (*setupWidgetIter)->size().y > size().y){
        pos.y = size().y - (*setupWidgetIter)->size().y;
    }

    (*setupWidgetIter)->pos(pos);
    
    if(manager_->getActiveTool() != NULL){
        std::list<SetupWidget*>::iterator curActiveSetupWidget = setupWidgets_.begin();
        std::advance(curActiveSetupWidget, manager_->getNActiveTool());

        (*curActiveSetupWidget)->visible(false);
    }

    (*setupWidgetIter)->visible(true);

    SetupWidget::ACTIVE_SETUP_WINDOW = (*setupWidgetIter);

    manager_->setActiveTool(n_tool);

    requireRender();
    return;
}

void ToolsList::ScrolledSlot(double ratio){

    std::list<SetupWidget*>::iterator setupWidgetIter = setupWidgets_.begin();
    std::advance(setupWidgetIter, manager_->getNActiveTool());

    (*setupWidgetIter)->visible(false);

    return;
}
