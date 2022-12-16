#include "ColorPicker.h"
#include "tools.hpp"
#include "Actions.h"

extern booba::ApplicationContext* booba::APPCONTEXT;

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

HSlider* SliderPicker::slider(){
    return slider_;
}

TextPicker::TextPicker(const std::string& name, int init_val, int minVal, int MaxVal):
    ContainerWidget({SETUP_WIDGET_WIDTH - 20, 40}),
    title_(new Label({40, 25})),
    storage_(new TextNumInsertWidget({SETUP_WIDGET_WIDTH - 20 - 50, 25}, init_val))
{
    title_->text(name);
    connect(title_, {3, 3});
    storage_->connectBy(title_, LINKAGE_MODE::RIGHT, 5);

    storage_->setDefaultText("0");
    storage_->setMinVal(minVal);
    storage_->setMaxVal(MaxVal);
}

TextPicker::~TextPicker(){
    delete title_;
    delete storage_;
}

TextNumInsertWidget* TextPicker::textField(){
    return storage_;
}

ColorSetup::ColorSetup(RectButton* controlButton):
    ContainerWidget({SETUP_WIDGET_WIDTH, SETUP_WIDGET_HEIGHT}),
    controlButton_(controlButton)
{

    Color curCol = convertFromsColor(booba::APPCONTEXT->fgColor);

    huePicker        = new SliderPicker("hue");
    saturationPicker = new SliderPicker("saturation");
    brightnessPicker = new SliderPicker("brightness");
    opacityPicker    = new SliderPicker("opacity");
    
    rPicker = new TextPicker("R", curCol.r(), 0, 255);
    gPicker = new TextPicker("G", curCol.g(), 0, 255);
    bPicker = new TextPicker("B", curCol.b(), 0, 255);
    aPicker = new TextPicker("A", curCol.a(), 0, 255);
    hexPicker = new TextPicker("HEX", static_cast<unsigned int>(curCol), 0, 0xFFFFFF);

    texture(Color::WHITE);
    connect(hexPicker, {5, 5});

    aPicker->connectBy(hexPicker, LINKAGE_MODE::TOP);
    bPicker->connectBy(aPicker, LINKAGE_MODE::TOP);
    gPicker->connectBy(bPicker, LINKAGE_MODE::TOP);
    rPicker->connectBy(gPicker, LINKAGE_MODE::TOP);

    opacityPicker->connectBy(rPicker, LINKAGE_MODE::TOP);
    brightnessPicker->connectBy(opacityPicker, LINKAGE_MODE::TOP);
    saturationPicker->connectBy(brightnessPicker, LINKAGE_MODE::TOP);
    huePicker->connectBy(saturationPicker, LINKAGE_MODE::TOP);

    rPicker->textField()->setHandler<ColorSetup>(this, &ColorSetup::rPickerInserted);
    gPicker->textField()->setHandler<ColorSetup>(this, &ColorSetup::gPickerInserted);
    bPicker->textField()->setHandler<ColorSetup>(this, &ColorSetup::bPickerInserted);
    aPicker->textField()->setHandler<ColorSetup>(this, &ColorSetup::aPickerInserted);

    opacityPicker->slider()->setHandler<ColorSetup>(this, &ColorSetup::opacityPickerInserted);
    brightnessPicker->slider()->setHandler<ColorSetup>(this, &ColorSetup::brightnessPickerInserted);
    saturationPicker->slider()->setHandler<ColorSetup>(this, &ColorSetup::saturationPickerInserted);
    huePicker->slider()->setHandler<ColorSetup>(this, &ColorSetup::huePickerInserted);
}

ColorSetup::~ColorSetup(){
    delete huePicker;
    delete saturationPicker;
    delete brightnessPicker;
    delete opacityPicker;
    delete rPicker;
    delete gPicker;
    delete bPicker;
    delete aPicker;
}

void ColorSetup::rPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    cur_col.r((uint8_t)std::stoi(data));

    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);

    controlButton_->texture(cur_col);
    controlButton_->requireRender();

    return;
}

void ColorSetup::gPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);

    cur_col.g((uint8_t)std::stoi(data));
    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);
    controlButton_->texture(cur_col);
    controlButton_->requireRender();

    return;
}

void ColorSetup::bPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    cur_col.b((uint8_t)std::stoi(data));
    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);
    controlButton_->texture(cur_col);
    controlButton_->requireRender();

    return;
}

void ColorSetup::aPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    cur_col.a((uint8_t)std::stoi(data));
    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);
    controlButton_->texture(cur_col);
    controlButton_->requireRender();

    return;
}

void ColorSetup::hexPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    cur_col = std::stoi(data, 0, 16);
    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);
    controlButton_->texture(cur_col);
    controlButton_->requireRender();

    return;
}

void ColorSetup::opacityPickerInserted(double ratio){

    ;
}

void ColorSetup::brightnessPickerInserted(double ratio){

    ;
}

void ColorSetup::saturationPickerInserted(double ratio){

    ;
}

void ColorSetup::huePickerInserted(double ratio){

    ;
}

ColorPicker::ColorPicker():
    ContainerWidget({CONTROL_BUTT_WIDTH + SETUP_WIDGET_WIDTH, CONTROL_BUTT_HEIGHT + SETUP_WIDGET_HEIGHT}),
    control_button_(new RectButton({CONTROL_BUTT_WIDTH, CONTROL_BUTT_HEIGHT})),
    setup_widget_(new ColorSetup(control_button_))
{
    bgLayer_->transparency(0);

    // TODO: fix frames
    control_button_->texture(convertFromsColor(booba::APPCONTEXT->fgColor), false);
    connect(control_button_, {SETUP_WIDGET_WIDTH, 0});
    connect(setup_widget_, {0, CONTROL_BUTT_HEIGHT});

    control_button_->addHandler(new ObjAction<ColorSetup>(setup_widget_, &ColorSetup::invertVisible));
}

ColorPicker::~ColorPicker(){
    delete control_button_;
    delete setup_widget_;
}
