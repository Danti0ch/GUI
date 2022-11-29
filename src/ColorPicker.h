#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include "RectButton.h"

class SliderPicker : ContainerWidget{
public:
    SliderPicker(const std::string& name);

    PixelBuffer* buff();
private:
    PixelBuffer* buff_;
};

class TextPicker : ContainerWidget{
public:
    TextPicker(const std::string& name);
    
private:
    TextInsertWidget* storage_;
};

class ColorSetup : ContainerWidget{
public:
    ColorSetup(uint width, uint height);

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

class ColorPicker : ContainerWidget{
public:
    ColorPicker();

private:
    RectButton<ContainerWidget, bool> control_button_;
    ColorSetup setup_widget_;
};

#endif // COLOR_PICKER_H
