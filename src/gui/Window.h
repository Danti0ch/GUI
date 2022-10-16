#ifndef WINDOW_H
#define WINDOW_H

class Window{

    void exec(){
        while(isOpen()){
            while(space.extractEvent(event))
        }
    }
private:
    GraphicSpace space;
};

#endif // WINDOW_H
