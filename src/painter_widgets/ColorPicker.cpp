#include "ColorPicker.h"
#include "tools.hpp"

/*
extern booba::ApplicationContext* APPCONTEXT;

const uint CONTROL_BUTT_WIDTH  = 50;
const uint CONTROL_BUTT_HEIGHT = 50;

const uint SETUP_WIDGET_WIDTH  = 200;
const uint SETUP_WIDGET_HEIGHT = 400;

SliderPicker::SliderPicker(const std::string& name):
    ContainerWidget({SETUP_WIDGET_WIDTH - 20, 40}),
    title_(new Label({SETUP_WIDGET_WIDTH - 20, 15})),
    slider_(new HSlider({SETUP_WIDGET_WIDTH - 20, 15}))
{
    title_->text(name);
    connect(slider_, {3, 3});

    title_->connectBy(slider_, LINKAGE_MODE::TOP, 5);
};

const HSlider* SliderPicker::slider() const{
    return slider_;
}

TextPicker::TextPicker(const std::string& name):
    ContainerWidget({SETUP_WIDGET_WIDTH - 20, 40}),
    title_(new Label({SETUP_WIDGET_WIDTH - 20, 15})),
    storage_(new TextInsertWidget(SETUP_WIDGET_WIDTH - 20, 15))
{
    title_->text(name);

    connect(storage_, {3, 3});

    title_->connectBy(storage_, LINKAGE_MODE::TOP, 5);
}

TextPicker::~TextPicker(){
    delete title_;
    delete storage_;
}

const TextInsertWidget* textField() const{
    return storage_;
}

ColorSetup::ColorSetup(uint width, uint height):
    ContainerWidget({width, height}),
    huePicker("hue"),
    saturationPicker("saturation"),
    brightnessPicker("brightness"),
    opacityPicker("opacity"),

    rPicker("R"),
    gPicker("G"),
    bPicker("B"),
    aPicker("A"),
    hexPicker("HEX")
{
    connect(&hexPicker, {5, 5});

    aPicker.connectBy(&hexPicker, LINKAGE_MODE::TOP);
    bPicker.connectBy(&aPicker, LINKAGE_MODE::TOP);
    gPicker.connectBy(&bPicker, LINKAGE_MODE::TOP);
    rPicker.connectBy(&gPicker, LINKAGE_MODE::TOP);

    opacityPicker.connectBy(&rPicker, LINKAGE_MODE::TOP);
    brightnessPicker.connectBy(&opacityPicker, LINKAGE_MODE::TOP);
    saturationPicker.connectBy(&brightnessPicker, LINKAGE_MODE::TOP);
    huePicker.connectBy(&saturationPicker, LINKAGE_MODE::TOP);
}

/*
void ColorSetup::onTextInserted(const TextInsertedEvent* event){

    const Widget* p_field = event->p_field();
    if(p_field != &rPicker && p_field != &gPicker && p_field != &bPicker && p_field != &aPicker && p_field != &hexPicker){
        return;
    }

    Color cur_col(APPCONTEXT->fgColor);
    const std::string& data = event->data();

    if(p_field == &hexPicker){
        // TODO:
    }
    else if(p_field == &aPicker){
        cur_col.a((uint8_t)std::stoi(data));
    }
    else if(p_field == &bPicker){
        cur_col.b((uint8_t)std::stoi(data));
    }
    else if(p_field == &gPicker){
        cur_col.g((uint8_t)std::stoi(data));
    }
    else if(p_field == &rPicker){
        cur_col.r((uint8_t)std::stoi(data));
    }

    APPCONTEXT->fgColor = cur_col;

}
*/

/*
void ColorSetup::onSliderMoved(const SliderMovedEvent* event){

    const Widget* p_slider = event->p_slider();
    if(p_slider != &huePicker && p_slider != &saturationPicker && p_slider != &brightnessPicker && p_slider != &opacityPicker){
        return;
    }

}

ColorPicker::ColorPicker():
    ContainerWidget({CONTROL_BUTT_WIDTH + SETUP_WIDGET_WIDTH, CONTROL_BUTT_HEIGHT + SETUP_WIDGET_HEIGHT}),
    control_button_(new RectButton({CONTROL_BUTT_WIDTH, CONTROL_BUTT_HEIGHT})),
    setup_widget_(new ColorSetup({SETUP_WIDGET_WIDTH, SETUP_WIDGET_HEIGHT}))
{
    texture().setTransparency(0);
    control_button_.setTexture(Color(40, 40, 40));
    connect(&control_button_, SETUP_WIDGET_WIDTH, 0);
    connect(&setup_widget_, 0, CONTROL_BUTT_HEIGHT);

    control_button_.handler(&setup_widget_, &ContainerWidget::changeVisible);
}
*/
