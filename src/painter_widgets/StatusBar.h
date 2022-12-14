#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include "Widget.h"
#include "Label.h"

class StatusBar : public ContainerWidget{
public:
    StatusBar();
    ~StatusBar();
    
    void setPluginCounter(uint n_plugins);
    void setActivePluginName(const std::string& name);
private:

    Label* plugin_counter_;
    Label* cur_plugin_name_;
    Label* greetings_str_;
};

#endif // STATUS_BAR_H
