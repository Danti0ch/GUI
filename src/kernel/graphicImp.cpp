#include "graphicImp.h"
#include "logger.h"

const coord FRAME_DEPTH = 1;

RealWindow::RealWindow(Vector size, unsigned int extractedEventsQueueMaxSize):
    extractedEventsQueueMaxSize_(extractedEventsQueueMaxSize),
    size_(size),
    buffer_(NULL)
{}

RealWindow::~RealWindow(){

    while(!extractedEvents.empty()){
        Event* ev = extractedEvents.front();
        extractedEvents.pop();
        delete ev;
    }
}

void RealWindow::extractEvents(){

    Event* storage = NULL;
    while(extractedEvents.size() <= extractedEventsQueueMaxSize_ && extractEvent(&storage)){
        NASSERT(storage);
        extractedEvents.push(storage);
    }

    return;
}

RenderObject* RealWindow::buffer(){ return buffer_; }

void RenderObject::drawCentralized(const Text& data){

    drawText((size() - getTextSize(data)) / 2, data);
    return;
}

void RenderObject::draw(Vector point, const Text& data){
    drawText(point, data);
    return;
}

void drawFrame(DrawableArea* area, Color col){

    for(uint x = 0; x < area->size().x; x++){
        for(int depth = 0; depth < FRAME_DEPTH; depth++){
            area->setPixel({x, depth}, col);
            area->setPixel({x, area->size().y - depth - 1}, col);
        }
    }

    for(uint y = 0; y < area->size().y; y++){
        for(int depth = 0; depth < FRAME_DEPTH; depth++){
            area->setPixel({depth, y}, col);
            area->setPixel({area->size().x - depth - 1, y}, col);
        }
    }

    return;
}
