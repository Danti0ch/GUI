/**
 * @brief funcs defs to enable components work with gui instruments
 * 
 */
#include "tools.hpp"
#include "Buttons.h"
#include "ToolManager.h"
#include "Slider.h"
#include "CanvasWidget.h"
#include "SetupWidget.h"
#include "CanvasManager.h"
#include "EventWrapper.h"

stImage* stImage::hiddenLayerWrapper = NULL;

//extern "C" uint64_t booba::createButton(int32_t x, int32_t y, uint32_t w, uint32_t h, const char* name = nullptr){
    
    // TODO: make button without params
    /*
    RectButton* button = new RectButton({x, y}, w, h);

    if(name != nullptr){
        button->setText(name);
    }

    return reinterpret_cast<uint64_t>(button);
    */
  //  exit(0);

    //return 0;
//}

// TODO:
extern "C" bool booba::setToolBarSize(size_t w, size_t h){
    ;
}

extern "C" uint64_t booba::createLabel(size_t x, size_t y, size_t w, size_t h, const char* text){
    
    Label* label = new Label({w, h});
    label->text(text);
    
    SetupWidget::ACTIVE_SETUP_WINDOW->addSetupWidget(label, {x, y});
    return (uint64_t)(label);
}

extern "C" uint64_t booba::createSlider(size_t x, size_t y, size_t w, size_t h, int64_t minValue, int64_t maxValue, int64_t startValue){

    // TODO:
    HSlider* slider = new HSlider(Vector(w, h));

    SetupWidget::ACTIVE_SETUP_WINDOW->addSetupWidget(slider, {x, y});

    slider->setHandlerIdent<ToolManager>(ToolManager::ACTIVE_TOOL_MANAGER, &ToolManager::setupSliderMoved);
    return (uint64_t)(slider);
}

extern "C" void booba::addTool(Tool* tool){
    
    ToolManager::ACTIVE_TOOL_MANAGER->addTool(tool);
    return;
}

extern "C" booba::Image* booba::getHiddenLayerID(){

    return stImage::hiddenLayerWrapper;
}

extern "C" uint64_t booba::createCanvas(size_t x, size_t y, size_t w, size_t h){

    CanvasWidget* canvas = new CanvasWidget({w, h}, ToolManager::ACTIVE_TOOL_MANAGER);

    SetupWidget::ACTIVE_SETUP_WINDOW->addSetupWidget(canvas, {x, y});

    return (uint64_t)(canvas);
}

extern "C" uint64_t booba::createButton(size_t x, size_t y, size_t w, size_t h, const char* text){

    RectButton* butt = NULL;
    if(!text)
        butt = new RectButton({w, h});
    else 
        butt = new RectButton({w, h}, text);
    
    SetupWidget::ACTIVE_SETUP_WINDOW->addSetupWidget(butt, {x, y});

    return (uint64_t)(butt);
}

extern "C" void booba::putPixel(uint64_t canvas, size_t x, size_t y, uint32_t color){
    CanvasWidget* widget = (CanvasWidget*)canvas;

    widget->drawableLayer()->setPixel({x, y}, convertFromsColor(color));
}
