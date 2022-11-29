/**
 * @brief funcs defs to enable components work with gui instruments
 * 
 */
// TODO: rename
#include "tools.hpp"
#include "RectButton.h"
#include "ToolManager.h"
#include "Slider.h"
#include "CanvasWidget.h"

extern "C" uint64_t booba::createButton(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name = nullptr){
    
    // TODO: make button without params
    /*RectButton<int>* button = new RectButton<int>(x, y, w, h);

    if(name != nullptr){
        button->setText(name);
    }

    return reinterpret_cast<uint64_t>(button);*/

    exit(0);

    return 0;
}

extern "C" uint64_t booba::createLabel(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name = nullptr){
    
    Label* label = new Label(w, h);
    label->text(name);
    
    ToolManager::ACTIVE_SETUP_WINDOW->connect(label, x, y);
    ToolManager::ACTIVE_TOOL_MANAGER->addSetupWidget(label);
    return 0;
}

extern "C" uint64_t booba::createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h){

    HSlider* slider = new HSlider(w, h, 10);
    slider->setTexture(Color(149, 54, 41));
    
    ToolManager::ACTIVE_SETUP_WINDOW->connect(slider, x, y);
    ToolManager::ACTIVE_TOOL_MANAGER->addSetupWidget(slider);

    return 0;
}

extern "C" uint64_t booba::createCanvas(int32_t x, int32_t y, int32_t w, int32_t h){

    assert(0);
    //CanvasWidget* canvas = new CanvasWidget(w, h, )
    return 0;
}

extern "C" uint64_t booba::putPixel (uint64_t canvas, int32_t x, int32_t y, uint32_t color){
    // TODO:

    exit(0);
    return 0;
}

extern "C" uint64_t booba::putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture){
    // TODO:

    exit(0);
    return 0;
}

extern "C" void booba::addTool(Tool* tool){
    
    ToolManager::ACTIVE_TOOL_MANAGER->addTool(tool);
    return;
}

extern "C" void booba::addFilter(Tool* tool){
    // TODO:

    exit(0);
    return;
}
