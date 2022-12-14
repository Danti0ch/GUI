#include "StatusBar.h"
#include "Settings.h"

static const uint HEIGHT = 20;
StatusBar::StatusBar():
    ContainerWidget({WINDOW_WIDTH, HEIGHT}),
    greetings_str_(new Label({180, HEIGHT}, "Greetings Dear Users!")),
    plugin_counter_(new Label({60, HEIGHT})),
    cur_plugin_name_(new Label({140, HEIGHT}))
{
    ContainerWidget::connect(greetings_str_, {0, 0});

    plugin_counter_->connectBy(greetings_str_, LINKAGE_MODE::RIGHT, 5);
    cur_plugin_name_->connectBy(plugin_counter_, LINKAGE_MODE::RIGHT, 5);
        
    bgLayer_->clear(Color(51, 153, 255));

    Color labels_col(33, 96, 196);

    greetings_str_->texture(labels_col);
    plugin_counter_->texture(labels_col);
    cur_plugin_name_->texture(labels_col);
}

StatusBar::~StatusBar(){
    delete greetings_str_;
    delete plugin_counter_;
    delete cur_plugin_name_;
}

void StatusBar::setPluginCounter(uint n_plugins){
    plugin_counter_->text(std::to_string(n_plugins));
    return;
}

void StatusBar::setActivePluginName(const std::string& name){
    cur_plugin_name_->text(name);
    return;
}
