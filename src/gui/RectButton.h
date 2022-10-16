#ifndef RECT_BUTT_H
#define RECT_BUTT_H

// TODO: we want buttons with no T_DATA ??
typedef<typename T_DATA>
class RectButton : public AbstractButton<T_DATA>{
public:

    AbstractButton(uint x, uint y, uint width, uint height, const T_DATA& data, const Texture& texture, std::string& text = "", uint font_size):
        Widget(x, y, width, height, data, texture),
        text_(text, font_size)
    {}

    AbstractButton(uint x, uint y, uint width, uint height, const T_DATA& data, const Texture& texture, std::string text):
        Widget(x, y, width, height, data, texture),
        text_(text)
    {}

    AbstractButton(uint x, uint y, uint width, uint height, const T_DATA& data, const Texture& texture):
        Widget(x, y, width, height, data, texture),
        text_()
    {}

    AbstractButton(uint x, uint y, uint width, uint height, const T_DATA& data, const Texture& texture):
        Widget(x, y, width, height, data, texture),
        text_()
    {}

    virtual void draw() override{
        if(space_ == NULL) return;
        text_.Draw(p_space_, x + 4, y + height / 2);
    }
private:
    Text text_;
    T_DATA data_;
};

#endif // RECT_BUTT_H
