#include "SetupWidget.h"
#include "CanvasManager.h"

SetupWidget::SetupWidget(ToolManager* tool_manager):
    Expended({200, 200}),
    tool_manager_(tool_manager),
    setupWindowWidgets_()
{}

SetupWidget::~SetupWidget(){
    for(auto widget: setupWindowWidgets_){
        delete widget;
    }
}

void SetupWidget::onMouseButtonPressed(const MouseButtonPressedEvent* event){

    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET, event);
    requireRender();
}

void SetupWidget::onMouseButtonReleased( const MouseButtonReleasedEvent* event){
    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET, event);
    requireRender();
}

void SetupWidget::onMouseMoved(const MouseMovedEvent* event){
    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET, event);
    requireRender();
}

void SetupWidget::onKeyPressed( const KeyPressedEvent* event){
    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET, event);
    requireRender();
}

void SetupWidget::onKeyReleased( const KeyReleasedEvent* event){
    tool_manager_->apply(CanvasManager::ACTIVE_CANVAS_WIDGET, event);
    requireRender();
}

void SetupWidget::addSetupWidget(Widget* widget, Vector pos){
    connect(widget, pos);
    setupWindowWidgets_.push_back(widget);
}

SetupWidget* SetupWidget::ACTIVE_SETUP_WINDOW = NULL;
