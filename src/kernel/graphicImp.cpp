#include "graphicImp.h"
#include "logger.h"

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
