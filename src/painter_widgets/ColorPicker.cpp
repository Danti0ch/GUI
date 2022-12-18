#include "ColorPicker.h"
#include "tools.hpp"
#include "Actions.h"

extern booba::ApplicationContext* booba::APPCONTEXT;

const uint CONTROL_BUTT_WIDTH  = 50;
const uint CONTROL_BUTT_HEIGHT = 50;

const uint SETUP_WIDGET_WIDTH  = 200;
const uint SETUP_WIDGET_HEIGHT = 400;

SliderPicker::SliderPicker(const std::string& name, ProportionRatio initRatio):
    ContainerWidget({SETUP_WIDGET_WIDTH - 20, 40}),
    title_(new Label({SETUP_WIDGET_WIDTH - 20, 15})),
    slider_(new HSlider({SETUP_WIDGET_WIDTH - 20, 15}, initRatio))
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

    huePicker        = new SliderPicker("hue", (double)curCol.h() / (double)360);
    saturationPicker = new SliderPicker("saturation", curCol.s());
    brightnessPicker = new SliderPicker("brightness", curCol.v());
    
    rPicker = new TextPicker("R", curCol.r(), 0, 255);
    gPicker = new TextPicker("G", curCol.g(), 0, 255);
    bPicker = new TextPicker("B", curCol.b(), 0, 255);
    hexPicker = new TextPicker("HEX", static_cast<unsigned int>(curCol), 0, 0xFFFFFF);

    texture(Color::WHITE);
    connect(hexPicker, {5, 5});

    bPicker->connectBy(hexPicker, LINKAGE_MODE::TOP);
    gPicker->connectBy(bPicker, LINKAGE_MODE::TOP);
    rPicker->connectBy(gPicker, LINKAGE_MODE::TOP);

    brightnessPicker->connectBy(rPicker, LINKAGE_MODE::TOP);
    saturationPicker->connectBy(brightnessPicker, LINKAGE_MODE::TOP);
    huePicker->connectBy(saturationPicker, LINKAGE_MODE::TOP);

    rPicker->textField()->setHandler<ColorSetup>(this, &ColorSetup::rPickerInserted);
    gPicker->textField()->setHandler<ColorSetup>(this, &ColorSetup::gPickerInserted);
    bPicker->textField()->setHandler<ColorSetup>(this, &ColorSetup::bPickerInserted);

    brightnessPicker->slider()->setHandler<ColorSetup>(this, &ColorSetup::brightnessPickerInserted);
    saturationPicker->slider()->setHandler<ColorSetup>(this, &ColorSetup::saturationPickerInserted);
    huePicker->slider()->setHandler<ColorSetup>(this, &ColorSetup::huePickerInserted);

    colorArea_ = CREATE_DRAWABLE_AREA(Vector(SETUP_WIDGET_WIDTH - 10, 110));
}

ColorSetup::~ColorSetup(){
    delete huePicker;
    delete saturationPicker;
    delete brightnessPicker;
    delete rPicker;
    delete gPicker;
    delete bPicker;

    delete colorArea_;
}

// TODO: remove copypaste
void ColorSetup::rPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    cur_col.r((uint8_t)std::stoi(data));

    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);

    updatePickers();
    return;
}

void ColorSetup::gPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    cur_col.g((uint8_t)std::stoi(data));
    
    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);

    updatePickers();
    return;
}

void ColorSetup::bPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    cur_col.b((uint8_t)std::stoi(data));
    
    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);

    updatePickers();
    return;
}

void ColorSetup::hexPickerInserted(std::string data){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    cur_col = std::stoi(data, 0, 16);
    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);

    updatePickers();
    return;
}

void ColorSetup::brightnessPickerInserted(double ratio){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    
    cur_col.v(ratio);

    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);
    
    updatePickers();
    return;
}

void ColorSetup::saturationPickerInserted(double ratio){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    
    cur_col.s(ratio);

    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);

    updatePickers();
    return;
}

void ColorSetup::huePickerInserted(double ratio){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);
    
    cur_col.h((unsigned int)(360.0 * ratio));
    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);

    updatePickers();
    return;
}

void ColorSetup::updatePickers(){

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);

    rPicker->textField()->set(cur_col.r());
    gPicker->textField()->set(cur_col.g());
    bPicker->textField()->set(cur_col.b());
    hexPicker->textField()->set(cur_col);

    huePicker->slider()->replaceIndicator(((double)cur_col.h()) / (double)360);
    saturationPicker->slider()->replaceIndicator(cur_col.s());
    brightnessPicker->slider()->replaceIndicator(cur_col.v());

    controlButton_->texture(cur_col);
    controlButton_->requireRender();

    return;
}

void ColorSetup::colorAreaUpdate(){

    for(coord y = 0; y < colorArea_->size().y; y++){
        for(coord x = 0; x < colorArea_->size().x; x++){
            Color col = convertFromsColor(booba::APPCONTEXT->fgColor);
            col.hsv(col.h(), (double)x / (double)colorArea_->size().x, (double)y / (double)colorArea_->size().y);

            colorArea_->setPixel({x, y}, col);
        }
    }

    return;
}

// TODO: refactor
void ColorSetup::onMouseButtonPressed(const MouseButtonPressedEvent* event){

    // TODO: fix hard code coords
    Vector colorAreaPos = {5, SETUP_WIDGET_HEIGHT - 5 - colorArea_->size().y};

    if(!isPointInside(RectangleArea({realPos().x + colorAreaPos.x, realPos().y + colorAreaPos.y}, colorArea_->size()), ManipulatorsContext::activeContext.mousePos())){
        return;
    }

    Color cur_col = convertFromsColor(booba::APPCONTEXT->fgColor);


    cur_col.s((double)(ManipulatorsContext::activeContext.mousePos().x - realPos().x - colorAreaPos.x) / (double)colorArea_->size().x);
    cur_col.v((double)(ManipulatorsContext::activeContext.mousePos().y - realPos().y - colorAreaPos.y) / (double)colorArea_->size().y);

    booba::APPCONTEXT->fgColor = convertTosColor(cur_col);

    updatePickers();
    return;
}

void ColorSetup::draw(){

    colorAreaUpdate();
    buffer_->draw({5, SETUP_WIDGET_HEIGHT - 5 - colorArea_->size().y}, colorArea_);

    ContainerWidget::draw();
    return;
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
    setup_widget_->visible(false);
}

ColorPicker::~ColorPicker(){
    delete control_button_;
    delete setup_widget_;
}
