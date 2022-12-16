#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "Buttons.h"
#include "TextInsertWidget.h"
#include "Label.h"
#include "Slider.h"

class SliderPicker : public ContainerWidget{
public:
    SliderPicker(const std::string& name);

    HSlider* slider();
private:
    Label*   title_;
    HSlider* slider_;    
};

class TextPicker : public ContainerWidget{
public:
    TextPicker(const std::string& name, int init_val, int minVal, int MaxVal);
    ~TextPicker();

    TextNumInsertWidget* textField();
private:
    Label*             title_;
    TextNumInsertWidget*  storage_;
};

class ColorSetup : public ContainerWidget{
public:
    ColorSetup(RectButton* controlButton);
    ~ColorSetup();

    void rPickerInserted(std::string data);
    void gPickerInserted(std::string data);
    void bPickerInserted(std::string data);
    void aPickerInserted(std::string data);
    void hexPickerInserted(std::string data);

    void opacityPickerInserted(double ratio);
    void brightnessPickerInserted(double ratio);
    void saturationPickerInserted(double ratio);
    void huePickerInserted(double ratio);

private:
    SliderPicker* huePicker;
    SliderPicker* saturationPicker;
    SliderPicker* brightnessPicker;
    SliderPicker* opacityPicker;

    TextPicker* rPicker;
    TextPicker* gPicker;
    TextPicker* bPicker;
    TextPicker* aPicker;
    TextPicker* hexPicker;

    RectButton* controlButton_;
};

class ColorPicker : public ContainerWidget{
public:
    ColorPicker();
    ~ColorPicker();

private:
    RectButton* control_button_;
    ColorSetup* setup_widget_;
};

#endif // COLOR_PICKER_H
