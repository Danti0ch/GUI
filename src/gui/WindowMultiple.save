#ifndef APPLICATION_H
#define APPLICATION_H

class Application{

    Application():
        windows_(1){}
    
    ~Application(){}

    void addWindow(const Window& window){
        windows_.push_back(window);
    }

    void 
    // TODO:
    void exec(){
        
        std::list<Window>::iterator wd_iter;
        while(!windows_.empty()){

            wd_iter = windows_.begin();

            while(wd_iter < windows_.end()){
                if(wd_iter->isOpen()){
                    is_open = true;
                    wd_iter->pollEvents();
                    wd_iter++;
                }
                else{
                    wd_iter = windows_.erase(wd_iter);
                }
            }
        }
        return;
    }

private:
    std::list<Window> windows_;
};

#endif // APPLICATION_H
