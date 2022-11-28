#include "StandartTools.h"
#include <iostream>
#include <assert.h>
#include "logger.h"

static const uint POS_POISON = -1;
static const uint DEFAULT_PEN_SIZE = 5;

TOOL_INIT(TextInsertTool)

TextInsertTool::TextInsertTool():
    AbstractTool(),
    data_()
{}

void TextInsertTool::apply(booba::Image* image, const booba::Event* event) {

    return;
}
