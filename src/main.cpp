#include "Window.h"
#include <iostream>
#include "RectButton.h"
#include "CanvasWidget.h"
#include "Label.h"
#include "ExpendedContainerWidget.h"
#include "ListWidget.h"
#include "ToolsList.h"
void foo(uint tool_id){

    MDLOG("tool(%u) is pressed", tool_id);
    return;
}

void goo(uint canvas_id){

    MDLOG("canvas(%u) is shown", canvas_id);
    return;
}

int main(int argc, char *argv[]){

    Window cur_window(1080, 720);

    cur_window.setTexture(Color(123, 123, 123));
    
    cur_window.add(&status_bar);

    ToolsList tools(740, 40, 150, 560);
    cur_window.add(&tools);

    CanvasWidget canvas(15, 40, 680, 560, tools.toolManager());
    canvas.setTexture(Color(255, 255, 255));

    cur_window.add(&canvas);

    /*HListWidget canvas_list(15, 600, 680, 20, 80);
    canvas_list.setTexture(Color(255, 153, 204));
    canvas_list.add("canvas1", goo);
    canvas_list.add("canvas2", goo);
    canvas_list.add("canvas3", goo);
    
    cur_window.add(&canvas_list);

    VListWidget tools_list(740, 40, 150, 560, 30);
    tools_list.setTexture(Color(255, 153, 204));
    for(uint i = 0; i < 40; i++){
        tools_list.add("tool", foo);
    }

    cur_window.add(&tools_list);
    
    HListWidget setting_list(0, 700, 1080, 20, 80);
    setting_list.setTexture(Color(255, 153, 204));

    setting_list.add("file", foo);
    setting_list.add("other", foo);
    
    cur_window.add(&setting_list);
    */
    cur_window.exec();

    return 0;
}
