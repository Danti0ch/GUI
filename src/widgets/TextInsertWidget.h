#ifndef TEXT_INSERT_WIDGET_H
#define TEXT_INSERT_WIDGET_H

#include "Widget.h"

class TextInsertWidget : public Widget{
public:
    TextInsertWidget(uint width, uint height);
    
    void onKeyPressed( const KeyPressedEvent* event) override;

    void draw() override;
private:
    Text text_;
};

#endif // TEXT_INSERT_WIDGET_H
