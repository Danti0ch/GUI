#include "tests.h"
#include <string.h>

// TODO: fix arrow offsets
// TODO: искривление пространства изза масштабирования осей

int main(int argc, char *argv[]){

    if(argc < 2) return 0;

    if(!strcmp(argv[1], "sphere")){
        SphereRender space;
        space.Init();    
    }
    else if(!strcmp(argv[1], "vecs")){
        ActionVectorsRender space;
        space.Init();
    }
    else if(!strcmp(argv[1], "ray")){
        SceneRaytracer space;
        space.Init();
    }
    
    return 0;
}
