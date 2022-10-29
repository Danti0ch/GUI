#ifndef WINDOW_H
#define WINDOW_H

class Window : public ContainerWidget{
public:
    Window(uint width, uint height);

    void exec(){
        Event* event = NULL;
        bool was_event = false;

        LocPixBuffer loc_pix_buf(&pix_buf_, 0, 0, width(), height());
        fullDraw(&loc_pix_buf);

        space_.show();

        while(space_.isOpen()){
            while(space_.extractEvent(&event)){
                was_event = true;
                event_manager_.processHandlers(event);
                delete event;
            }
            if(was_event){
                fullDraw(&loc_pix_buf);
                space_.show();
                was_event = false;
            }
        }

        return;
    }

private:
    GraphicSpace space_;
    PixBuffer    pix_buf_;
};

#endif // WINDOW_H
