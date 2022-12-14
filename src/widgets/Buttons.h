#ifndef ABSTRACT_BUTTON_H
#define ABSTRACT_BUTTON_H

#include "Widget.h"
#include "Hovered.h"
#include "Actions.h"

class AbstractButton : public Hovered{
public:

    AbstractButton(Vector size);
    ~AbstractButton();

    void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;

    void addHandler(Action* action);
private:
    MacroAction* actions_;
};

class RectButton : public AbstractButton{
public:
    RectButton(Vector size);
    RectButton(Vector size, const std::string& label);

    void draw() override;

    const std::string& label();
private:
    Text text_;
};

#endif // ABSTRACT_BUTTON_H
