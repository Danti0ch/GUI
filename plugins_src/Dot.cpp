#include "Dot.h"
#include <iostream>

void DotTool::apply(booba::Image* image, const booba::Event* event) {

    const int32_t sqSize = 4;

    if (event->type == booba::EventType::MousePressed) {
        uint32_t pixelsAmount = 0;
        
        for (int32_t curX = std::max(0, event->Oleg.mbedata.x - sqSize);     curX < std::min(int32_t(image->getX()), event->Oleg.mbedata.x + sqSize); curX++) {
            for (int32_t curY = std::max(0, event->Oleg.mbedata.y - sqSize); curY < std::min(int32_t(image->getH()), event->Oleg.mbedata.y + sqSize); curY++) {
                image->putPixel(curX, curY, 0);
                pixelsAmount++;
            }
        }
    }   
}

extern "C" void booba::init_module() {

    DotTool* dotTool = new DotTool();

    booba::addTool(dotTool);
}
