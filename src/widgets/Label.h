#ifndef LABEL_H
#define LABEL_H

#include "Widget.h"
#include "Auxil.h"

class Label : public Widget{
public:
    Label(Vector size);
    Label(Vector size, const std::string& text);
    ~Label() = default;

    void draw();
    
    const Text& text() const { return text_; }
    void text(const std::string& data);
private:
    Text text_;
};

#endif // LABEL_H
