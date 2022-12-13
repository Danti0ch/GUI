#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "RectButton.h"
#include "TextInsertWidget.h"
#include "Label.h"
#include "Slider.h"

class SliderPicker : public ContainerWidget{
public:
    SliderPicker(const std::string& name);

    const HSlider* slider() const;
private:
    Label   title_;
    HSlider slider_;    
};

class TextPicker : public ContainerWidget{
public:
    TextPicker(const std::string& name);

    const TextInsertWidget* textField() const;
private:
    Label             title_;
    TextInsertWidget  storage_;
};

class ColorSetup : public ContainerWidget{
public:
    ColorSetup(uint width, uint height);

    void onTextInserted(const TextInsertedEvent* event) override;
    void onSliderMoved(const SliderMovedEvent* event) override;

private:
    SliderPicker huePicker;
    SliderPicker saturationPicker;
    SliderPicker brightnessPicker;
    SliderPicker opacityPicker;

    TextPicker rPicker;
    TextPicker gPicker;
    TextPicker bPicker;
    TextPicker aPicker;
    TextPicker hexPicker;
};

class ColorPicker : public ContainerWidget{
public:
    ColorPicker();

private:
    RectButton<ContainerWidget, bool> control_button_;
    ColorSetup setup_widget_;
};

#endif // COLOR_PICKER_H
