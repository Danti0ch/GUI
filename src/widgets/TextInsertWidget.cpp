#include "TextInsertWidget.h"
#include <string.h>

// TODO: implement setLetter mb for checking rules such numeric or etc
TextInsertWidget::TextInsertWidget(Vector size, std::string initText):
    Widget(size), text_(initText),
    actions_(new MacroAction()),
    defaultText_(initText),
    isDefault_(true)
{
    texture(0xe3e3e3, true);
}

TextInsertWidget::~TextInsertWidget(){
    delete actions_;
}

void TextInsertWidget::onKeyPressed(const KeyPressedEvent* event){

    if(event->key() == T_KEY::BackSpace && !text_.str.empty()){
        text_.str.pop_back();
        if(text_.str.empty()){
            text_.str = defaultText_;
            isDefault_ = true;
        }
    }
    else{
        char parsedSymb = convertKeyToChar(event->key(), ManipulatorsContext::activeContext);
        if(parsedSymb == 0) return;
        
        if(isDefault_){
            //?
            text_.str = "";
            isDefault_ = false;
        }
        text_.str.push_back(parsedSymb);
    }

    requireRender();

    actions_->execute();
    
    return;
}

void TextInsertWidget::draw(){

    buffer_->drawCentralized(text_);
    return;
}

void TextInsertWidget::setDefaultText(const std::string& defaultText){
    defaultText_ = defaultText;
    return;
}

TextNumInsertWidget::TextNumInsertWidget(Vector size, unsigned int init_val):
    TextInsertWidget(size, std::to_string(init_val)),
    isMinVal_(false), isMaxVal_(false)
{} 

void TextNumInsertWidget::onKeyPressed( const KeyPressedEvent* event){

    char symb = convertKeyToChar(event->key(), ManipulatorsContext::activeContext);
    if((symb != 0 && !isdigit(symb))) return;
    else if(symb){
        //?
        std::string new_str = text_.str;
        new_str.push_back(symb);

        int val = std::stoi(new_str);

        if(isMinVal_ && val < minVal_){
            set(minVal_);
            actions_->execute();
            return;
        }
        if(isMaxVal_ && val > maxVal_){
            set(maxVal_);
            actions_->execute();
            return;
        }
    }

    TextInsertWidget::onKeyPressed(event);

    return;
}

void TextNumInsertWidget::setDefaultText(const std::string& defaultText){
    
    bool isDigit = true;

    for(auto symb : defaultText){
        if(!isdigit(symb)){
            isDigit = false;
            break;
        }
    }

    int val = std::stoi(defaultText);

    if(isMinVal_ && val < minVal_){
        set(minVal_);
        return;
    }
    if(isMaxVal_ && val > maxVal_){
        set(maxVal_);
        return;
    }

    if(isDigit){
        TextInsertWidget::setDefaultText(defaultText);
    }

    return;
}

void TextNumInsertWidget::setMinVal(unsigned int val){
    isMinVal_ = true;
    minVal_ = val;

    return;
}

void TextNumInsertWidget::setMaxVal(unsigned int val){
    isMaxVal_ = true;
    maxVal_ = val;

    return;
}

void TextNumInsertWidget::set(unsigned int val){
    if(isMinVal_ && val < minVal_){
        val = minVal_;
    }
    if(isMaxVal_ && val > maxVal_){
        val = maxVal_;
    }

    text_.str = std::to_string(val);
    requireRender();

    return;
}
