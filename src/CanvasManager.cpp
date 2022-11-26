#include "CanvasManager.h"

static const uint CANVAS_MANAGER_WIDTH  = 600;
static const uint CANVAS_MANAGER_HEIGHT = 600;
static const uint CANVAS_LIST_HEIGHT = 15;
static const uint CANVAS_LIST_ELEM_WIDTH = 40;

static const uint DEFAULT_TEXT_WIDTH = CANVAS_MANAGER_WIDTH / 3;
/*
CanvasManager::CanvasManager(uint x, uint y):
    ContainerWidget(x, y, CANVAS_MANAGER_WIDTH, CANVAS_MANAGER_HEIGHT),
    canvas_list_(x, y + CANVAS_MANAGER_HEIGHT - CANVAS_LIST_HEIGHT, CANVAS_MANAGER_WIDTH, CANVAS_LIST_HEIGHT, CANVAS_LIST_ELEM_WIDTH, this, &CanvasManager::setActive),
    storage_(),
    default_text_(x + CANVAS_MANAGER_WIDTH / 3, y + CANVAS_LIST_HEIGHT / 2 - (Text::default_font_size / 2), DEFAULT_TEXT_WIDTH, )
{
    ContainerWidget::connect(&canvas_list_);
    canvas_list_.setVisible(false);

    setTexture(WHITE);
}
*/