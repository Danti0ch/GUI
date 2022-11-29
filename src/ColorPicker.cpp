#include "ColorPicker.h"

const uint CONTROL_BUTT_WIDTH  = 50;
const uint CONTROL_BUTT_HEIGHT = 50;

const uint SETUP_WIDGET_WIDTH  = 200;
const uint SETUP_WIDGET_HEIGHT = 300;

ColorPicker::ColorPicker():
    ContainerWidget(CONTROL_BUTT_WIDTH + SETUP_WIDGET_WIDTH, CONTROL_BUTT_HEIGHT + SETUP_WIDGET_HEIGHT),
    control_button_(CONTROL_BUTT_WIDTH, CONTROL_BUTT_HEIGHT),
    setup_widget_(SETUP_WIDGET_WIDTH, SETUP_WIDGET_HEIGHT)
{
    connect(&setup_widget_, 0, CONTROL_BUTT_HEIGHT);
    connect(&control_button_, &setup_widget_, LINKAGE_MODE::RIGHT, 0, -CONTROL_BUTT_HEIGHT);

    control_button_.handler(&setup_widget_, &ContainerWidget::changeVisible);
}
