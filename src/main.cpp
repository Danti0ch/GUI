#include "Window.h"
#include "Slider.h"

#include <iostream>

void wtf(int a){
    std::cout << a << "\n";
    return;
}
int main(int argc, char *argv[]){

    Window cur_window(720, 720);
    cur_window.setTexture(Color(200, 123, 123));

    HSlider slider(20, 20, 500, 20, 0.5);

    cur_window.connect(&slider);
    cur_window.exec();
    return 0;
}
