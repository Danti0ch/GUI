#include "CanvasManager.h"

const uint MANAGER_WIDTH  = 600;
const uint MANAGER_HEIGHT = 600;

const uint LIST_HEIGHT = 20;

// TODO: refactor
const uint CANVAS_WIDTH = MANAGER_WIDTH;
const uint CANVAS_HEIGHT = MANAGER_HEIGHT - LIST_HEIGHT;

CanvasWidget* CanvasManager::ACTIVE_CANVAS_WIDGET = NULL;
CanvasManager* CanvasManager::ACTIVE_CANVAS_MANAGER = NULL;

CanvasManager::CanvasManager(ToolManager* toolManager):
    ContainerWidget({MANAGER_WIDTH, MANAGER_HEIGHT}),
    canvas_list_(new HListWidget({MANAGER_WIDTH, LIST_HEIGHT})),
    storage_(),
    default_text_(new Label({150, 150}, "no canvas opened")),
    tool_manager_(toolManager),
    active_canvas(NULL),
    hiddenLayer_(CREATE_DRAWABLE_AREA(Vector(CANVAS_WIDTH, CANVAS_HEIGHT)))
{
    ContainerWidget::connect(canvas_list_, {0, MANAGER_HEIGHT - LIST_HEIGHT});
    ContainerWidget::connect(default_text_, {MANAGER_WIDTH / 2 - 50, MANAGER_HEIGHT / 2 - 50});

    bgLayer_->clear(Color::WHITE);

    ACTIVE_CANVAS_MANAGER = this;

    stImage::hiddenLayerWrapper = new stImage(hiddenLayer_);
}

CanvasManager::~CanvasManager(){
    std::list<CanvasStorage>::iterator iter;

    for(iter = storage_.begin(); iter != storage_.end(); iter++){
        delete (iter)->widget;
    }

    delete canvas_list_;
    delete default_text_;
    delete stImage::hiddenLayerWrapper;

    stImage::hiddenLayerWrapper = NULL;
}

void CanvasManager::setActive(uint n_canvas){
    assert(n_canvas < storage_.size());

    std::list<CanvasStorage>::iterator iter = storage_.begin();
    std::advance(iter, n_canvas);

    if(active_canvas != NULL){
        active_canvas->visible(false);
    }

    active_canvas = iter->widget;
    active_canvas->visible(true);

    ACTIVE_CANVAS_WIDGET = active_canvas;
    
    requireRender();
    return;
}

void CanvasManager::addCanvas(const std::string& path){
    CanvasStorage new_canvas;

    new_canvas.path = path;
    new_canvas.widget = new CanvasWidget({CANVAS_WIDTH, CANVAS_HEIGHT}, tool_manager_);
    new_canvas.widget->visible(false);

    storage_.push_back(new_canvas);

    new_canvas.widget->connectBy(canvas_list_, LINKAGE_MODE::BOTTOM);

    if(default_text_->isVisible()){

        default_text_->visible(false);
        canvas_list_->visible(true);
    }

    setActive(storage_.size() - 1);

    canvas_list_->add(path, new ObjArgAction<CanvasManager, uint>(this, &CanvasManager::setActive, storage_.size() - 1));
    return;
}

void CanvasManager::removeCanvas(const std::string& path){
    std::list<CanvasStorage>::iterator iter = storage_.begin();

    while(iter != storage_.end()){
        if(iter->path == path){

            ContainerWidget::remove(iter->widget);

            delete iter->widget;
            storage_.erase(iter++);
            break;
        }
        else iter++;
    }

    if(storage_.size() != 0){
        iter = storage_.begin();
        iter->widget->visible(true);
    }
    else{
        default_text_->visible(true);
        canvas_list_->visible(false);
    }

    // TODO:
    //canvas_list_.remove()
    return;
}

void CanvasManager::draw(){

    ContainerWidget::draw();
    
    buffer_->draw({0, 0}, hiddenLayer_);

    hiddenLayer_->clear(Color(0, 0, 0, 0));
}

DrawableArea* CanvasManager::hiddenLayer(){
    return hiddenLayer_;
}