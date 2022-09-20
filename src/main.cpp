#include "tests.h"
#include <string.h>

// TODO: fix arrow offsets
// TODO: искривление пространства изза масштабирования осей

int main(int argc, char *argv[]){

    if(argc > 1 && !strcmp(argv[1], "sphere")){
        SphereRender space;
        space.Init();    
    }
    else{
        ActionVectorsRender space;
        space.Init();
    }
    
    return 0;
}
