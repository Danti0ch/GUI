#include "ListWidget.h"

HListWidget::HListWidget(uint x, uint y, uint width, uint height, uint elem_width):
    ContainerWidget(x, y, width, height), elem_width_(elem_width), slider_(x, y, width, height / 10, 1)
{}
