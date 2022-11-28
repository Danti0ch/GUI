#include "StatusBar.h"
#include "Settings.h"

static const uint HEIGHT = 20;
StatusBar::StatusBar():
    ContainerWidget(WINDOW_WIDTH, HEIGHT),
    greetings_str_(180, HEIGHT),
    plugin_counter_(60, HEIGHT),
    cur_plugin_name_(140, HEIGHT)
{
    ContainerWidget::connect(&greetings_str_, 0, 0);
    ContainerWidget::connect(&plugin_counter_, &greetings_str_, LINKAGE_MODE::RIGHT, 5);
    ContainerWidget::connect(&cur_plugin_name_, &plugin_counter_, LINKAGE_MODE::RIGHT, 5);

    greetings_str_.text("Greetings Dear Users!");
    
    setTexture(Color(51, 153, 255));

    Color labels_col(33, 96, 196);

    greetings_str_.setTexture(labels_col);
    plugin_counter_.setTexture(labels_col);
    cur_plugin_name_.setTexture(labels_col);
}

void StatusBar::setPluginCounter(uint n_plugins){
    plugin_counter_.text(std::to_string(n_plugins));
    return;
}

void StatusBar::setActivePluginName(const std::string& name){
    cur_plugin_name_.text(name);
    return;
}