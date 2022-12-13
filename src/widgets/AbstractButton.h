#ifndef ABSTRACT_BUTTON_H
#define ABSTRACT_BUTTON_H

#include "Widget.h"

class AbstractButton : public Widget{
public:

    AbstractButton(Vector size);
    ~AbstractButton() = default;

    void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;
    void onMouseButtonReleased(const MouseButtonReleasedEvent* event) override;
    void onMouseMoved(const MouseMovedEvent* event) override;
    
    bool isHovered() const { return is_hovered_; }

    void setHoverTexture(const Color& col){ hover_texture_.setColor(col); RequireRender(); }

private:
    bool is_hovered_;

    // TODO: refactor
    stImage hover_texture_;
    stImage main_texture_;
};

#endif // ABSTRACT_BUTTON_H
