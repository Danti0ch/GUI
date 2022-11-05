#include "Window.h"
#include <iostream>

int main(int argc, char *argv[]){

    Window cur_window(720, 720);
    cur_window.setTexture(Color(123, 123, 123));
    
    cur_window.exec();
    return 0;
}
