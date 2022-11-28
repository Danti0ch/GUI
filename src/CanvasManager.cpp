#include "CanvasManager.h"

const uint MANAGER_WIDTH  = 600;
const uint MANAGER_HEIGHT = 600;

const uint LIST_HEIGHT = 20;

const uint CANVAS_WIDTH = MANAGER_WIDTH;
const uint CANVAS_HEIGHT = MANAGER_HEIGHT - LIST_HEIGHT;

CanvasManager::CanvasManager(ToolManager* toolManager):
    ContainerWidget(MANAGER_WIDTH, MANAGER_HEIGHT),
    canvas_list_(MANAGER_WIDTH, LIST_HEIGHT, 40, this, &CanvasManager::setActive),
    storage_(),
    default_text_(150, 150),
    tool_manager_(toolManager),
    active_canvas(NULL)
{
    ContainerWidget::connect(&canvas_list_, 0, MANAGER_HEIGHT - LIST_HEIGHT);
    ContainerWidget::connect(&default_text_, MANAGER_WIDTH / 2 - 50, MANAGER_HEIGHT / 2 - 50);
    default_text_.text("no canvas opened");

    canvas_list_.setVisible(false);

    setTexture(WHITE);
}

CanvasManager::~CanvasManager(){
    std::list<CanvasStorage>::iterator iter;

    for(iter = storage_.begin(); iter != storage_.end(); iter++){
        delete (iter)->widget;
    }
}

void CanvasManager::setActive(uint n_canvas){
    assert(n_canvas < storage_.size());

    std::list<CanvasStorage>::iterator iter = storage_.begin();
    std::advance(iter, n_canvas);

    if(active_canvas != NULL){
        active_canvas->setVisible(false);
    }
    active_canvas = iter->widget;
    active_canvas->setVisible(true);

    RequireRender();
    return;
}

void CanvasManager::addCanvas(const std::string& path){
    CanvasStorage new_canvas;

    new_canvas.path = path;
    new_canvas.widget = new CanvasWidget(CANVAS_WIDTH, CANVAS_HEIGHT, tool_manager_);
    new_canvas.widget->setVisible(false);

    storage_.push_back(new_canvas);
    std::cout << "yo: " << new_canvas.widget << "\n";
    ContainerWidget::connect(new_canvas.widget, &canvas_list_, LINKAGE_MODE::BOTTOM);

    if(default_text_.isVisible()){

        default_text_.setVisible(false);
        canvas_list_.setVisible(true);
    }

    setActive(storage_.size() - 1);

    canvas_list_.add(path);
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
        iter->widget->setVisible(true);
    }
    else{
        default_text_.setVisible(true);
        canvas_list_.setVisible(false);
    }

    // TODO:
    //canvas_list_.remove()
    return;
}

void CanvasManager::draw(){
    ContainerWidget::draw();
}
