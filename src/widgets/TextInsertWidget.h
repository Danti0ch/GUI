#ifndef TEXT_INSERT_WIDGET_H
#define TEXT_INSERT_WIDGET_H

#include "Widget.h"
#include "Actions.h"

// TODO: refactor
// TODO: add all keys support
// TODO: multiple line support?
class TextInsertWidget : public Widget{
public:
    TextInsertWidget(Vector size, std::string initText = "");
    ~TextInsertWidget();

    virtual void onKeyPressed( const KeyPressedEvent* event) override;

    void draw() override;
    virtual void setDefaultText(const std::string& defaultText);

    template<class T_RECEIVER>
    void setHandler(T_RECEIVER* pReceiver, void (T_RECEIVER::*slot)(std::string)){
        actions_->add(new ObjDynamicArgAction<T_RECEIVER, std::string>(pReceiver, slot, &this->text_.str));
        return;
    }

protected:
    Text text_;
    MacroAction* actions_;
private:
    std::string defaultText_;

    bool isDefault_;
};

class TextNumInsertWidget : public TextInsertWidget{
public:
    TextNumInsertWidget(Vector size, unsigned int init_val = 0);
    ~TextNumInsertWidget() = default;

    void onKeyPressed( const KeyPressedEvent* event) override;

    void setDefaultText(const std::string& defaultText) override;

    void setMinVal(unsigned int val);
    void setMaxVal(unsigned int val);

    void set(unsigned int val);
private:
    int minVal_, maxVal_;

    bool isMinVal_, isMaxVal_;
};

#endif // TEXT_INSERT_WIDGET_H
