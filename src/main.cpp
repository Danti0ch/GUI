#include "Window.h"
#include <iostream>
#include "RectButton.h"
#include "DrawableArea.h"
#include "Label.h"
#include "ExpendedContainerWidget.h"
#include "ListWidget.h"

void foo(int tool_id){

    MDLOG("tool(%u) is pressed", tool_id);
    return;
}

void goo(int canvas_id){

    MDLOG("canvas(%u) is shown", canvas_id);
    return;
}

int main(int argc, char *argv[]){

    Window cur_window(1080, 720);

    cur_window.setTexture(Color(123, 123, 123));
    
    Label status_bar(0, 0, cur_window.width(), 20);

    status_bar.setTexture(Color(51, 153, 255));
    status_bar.text("some data will be collected here");
    cur_window.add(&status_bar);

    HListWidget<int> canvas_list(15, 600, 680, 20, 80);
    canvas_list.setTexture(Color(255, 153, 204));
    canvas_list.add("canvas1", goo, 1);
    canvas_list.add("canvas2", goo, 2);
    canvas_list.add("canvas3", goo, 3);
    
    cur_window.add(&canvas_list);

    DrawableArea canvas(15, 40, 680, 560);
    canvas.setTexture(Color(255, 255, 255));

    cur_window.add(&canvas);

    VListWidget<int> tools_list(740, 40, 150, 560, 30);
    tools_list.setTexture(Color(255, 153, 204));
    for(uint i = 0; i < 40; i++){
        tools_list.add("tool", foo, i);
    }

    cur_window.add(&tools_list);
    
    HListWidget<int> setting_list(0, 700, 1080, 20, 80);
    setting_list.setTexture(Color(255, 153, 204));

    setting_list.add("file", foo, 1);
    setting_list.add("other", foo, 2);
    
    cur_window.add(&setting_list);
    cur_window.exec();

    return 0;
}
