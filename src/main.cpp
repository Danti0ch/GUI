#include "Window.h"
#include <iostream>
#include "RectButton.h"
#include "DrawableArea.h"
#include "Label.h"
#include "ExpendedContainerWidget.h"

void foo(int ga){
    std::cout<< "nig" << ga << "\n";
}
int main(int argc, char *argv[]){

    Window cur_window(720, 720);
    cur_window.setTexture(Color(123, 123, 123));

    ExpendedContainerWidget exp(10, 10, 100, 100, 8);
    
    exp.setTexture(Color(200, 0, 0));

    exp.ext_width(200);
    exp.ext_height(200);

    cur_window.add(&exp);

    cur_window.exec();
    return 0;
}
