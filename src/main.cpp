#include "Window.h"
#include <iostream>
#include "RectButton.h"
#include "DrawableArea.h"
#include "Label.h"
#include "ExpendedContainerWidget.h"
#include "ListWidget.h"

void foo(int ga){
    std::cout<< "nig" << ga << "\n";
}
int main(int argc, char *argv[]){

    Window cur_window(720, 720);
    cur_window.setTexture(Color(123, 123, 123));

    ExpendedContainerWidget exp(10, 10, 100, 100, 8);
    
    exp.setTexture(Color(200, 0, 0));

    cur_window.add(&exp);

    HListWidget<int> lst(200, 200, 200, 200, 60);
    lst.setTexture(Color(0, 255, 255));
    lst.add("wtf",  foo, 1);
    lst.add("wtf2", foo, 2);
    lst.add("wtf3", foo, 3);
    lst.add("wtf3", foo, 3);
    lst.add("wtf3", foo, 3);
    
    cur_window.add(&lst);    
    cur_window.exec();
    return 0;
}
