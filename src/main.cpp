#include "gui/Window.h"
#include "Raytracer.h"
#include "gui/Buttons.h"
#include "gui/DropMenu.h"
#include <iostream>

void ButtOK(const Event* event){
    std::cout << "OK\n";
}

int main(int argc, char *argv[]){

    Window cur_window(1080, 720);

    // TODO: эти координаты должны быть относительны
    // TODO: обязательно будем требовать наследование при конструировании?
    RectButton draw_butt(&cur_window, 700, 100, 100, 100);

    Text txt("draw this shit");
    txt.color(Color(0, 0, 0));
    draw_butt.setText(txt);
    draw_butt.setTexture(Texture(Color(16, 100, 115)));

    Raytracer tracer(&cur_window, 4, 4, 600, 600);
    draw_butt.addEventHandler(T_EVENT::mouseLClickEvent, ButtOK);

    cur_window.exec();
    return 0;
}
