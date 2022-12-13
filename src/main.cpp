#include "Window.h"
#include <iostream>
#include "RectButton.h"
#include "CanvasManager.h"
#include "Label.h"
#include "ExpendedContainerWidget.h"
#include "ListWidget.h"
#include "ToolsList.h"
#include "StatusBar.h"
#include "ColorPicker.h"

void foo(uint tool_id){

    MDLOG("tool(%u) is pressed", tool_id);
    return;
}

void goo(uint canvas_id){

    MDLOG("canvas(%u) is shown", canvas_id);
    return;
}

extern booba::ApplicationContext* APPCONTEXT;

int main(int argc, char *argv[]){

    Window cur_window(1080, 720);

    cur_window.setTexture(Color(123, 123, 123));

    StatusBar status_bar;
    cur_window.add(&status_bar, 0, 0);

    ToolsList tools;
    cur_window.add(&tools, &status_bar, LINKAGE_MODE::TOP, 15, 25);
    tools.toolManager()->linkStatusBar(&status_bar);

    status_bar.setPluginCounter(tools.toolManager()->tools().size());

    CanvasManager canvases(tools.toolManager());
    canvases.addCanvas("lol");
    canvases.addCanvas("kek");
    cur_window.add(&canvases, &tools, LINKAGE_MODE::RIGHT, 15);

    ColorPicker col_picker;
    cur_window.add(&col_picker, 800, 50);

    cur_window.exec();

    return 0;
}
