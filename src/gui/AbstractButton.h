#ifndef ABSTRACT_BUTT_H
#define ABSTRACT_BUTT_H

// TODO: Texture visible
typedef<typename T_DATA>
class AbstractButton : public Widget{
public:

    AbstractButton(uint x, uint y, uint width, uint height, const T_DATA& data, const Texture& texture = , std::string& text = "", uint font_size):
        Widget(x, y, width, height, data, texture),
        text_(text, font_size)
    {}

    AbstractButton(uint x, uint y, uint width, uint height, T_DATA data, Texture texture, std::string text):
        Widget(x, y, width, height, data, texture),
        text_(text)
    {}

    AbstractButton(uint x, uint y, uint width, uint height, T_DATA data, Texture texture):
        Widget(x, y, width, height, data, texture),
        text_()
    {}

    virtual void draw() override{
        if(space_ == NULL) return;
        text_.Draw(p_space_, x + 4, y + height / 2);
    }
private:
    Text text_;
};

#endif // ABSTRACT_BUTT_H
