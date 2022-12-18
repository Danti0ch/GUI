#include "TopBar.h"
#include "CanvasManager.h"

const coord LIST_ITEM_SIZE = 20;

TopBar::TopBar():
    hBarWidget({WINDOW_WIDTH, WINDOW_HEIGHT}, false, LIST_ITEM_SIZE)
{
    add("file", new FileDropList());
}

// TODO: redo
const uint N_FILE_ITEMS = 3;

FileDropList::FileDropList():
    VListWidget({80, N_FILE_ITEMS * VListWidget::DEFAULT_ITEM_SIZE})
{
    add("new", new ObjArgAction<CanvasManager, std::string>(CanvasManager::ACTIVE_CANVAS_MANAGER, &CanvasManager::addCanvas, "untitled"));
    add("open", new FuncAction<void (*)()>(openFile));
    add("save", new FuncArgAction<void (*)(const std::string&), const std::string&>(saveFile, "wtf"));
}

std::string getFileName(std::string& path){

    size_t nameSize = 0;
    for(int n_symb = path.size() - 1; n_symb >= 0; n_symb--, nameSize++){
        if(path[n_symb] == '/'){
            break;
        }
    }

    std::string name;
    for(int n_symb = 0; n_symb < nameSize; n_symb++){
        name.push_back(path[path.size() - 1 - n_symb]);
    }

    return name;
}

// TODO:
void openFile(){

    int aa = 1;
    char filename[1024] = "";
    FILE *f = popen("zenity --file-selection", "r");
    fgets(filename, 1024, f);

    MDLOG("%u %u %u", filename[0], filename[1], filename[2]);
    std::string canvasFilePath(filename);
    std::string canvasName = getFileName(canvasFilePath);

    MDLOG("%s", canvasFilePath);
    CanvasManager::ACTIVE_CANVAS_MANAGER->addCanvas(canvasName);

    //CanvasManager::ACTIVE_CANVAS_WIDGET->drawableLayer()->drawImage()
    
    return;
}

void saveFile(const std::string& name){
    
    return;
}
