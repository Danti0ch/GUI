#ifndef CONTEXTED_H
#define CONTEXTED_H

#include "Widget.h"
#include "ListWidget.h"

class Contexted : public Widget{
public:
    Contexted(Vector size, unsigned int nItems);
    ~Contexted();

    void onMouseButtonPressed(const MouseButtonPressedEvent* event) override;

    void addItem(const std::string& name, Action* action);

private:
    VListWidget* contextMenu_;
};

#endif // CONTEXTED_H
