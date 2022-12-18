#include "Window.h"
#include <iostream>
#include "Buttons.h"
#include "CanvasManager.h"
#include "Label.h"
#include "ListWidget.h"
#include "ToolsList.h"
#include "StatusBar.h"
#include "ColorPicker.h"
#include "TopBar.h"

booba::ApplicationContext* booba::APPCONTEXT = NULL;

template<typename... T>
class A{
public:
    A(){
        std::cout << "safsdf\n";
    }
};


// TODO: global get Color
int main(int argc, char *argv[]){

    booba::APPCONTEXT = new booba::ApplicationContext();
    booba::APPCONTEXT->fgColor = convertTosColor(Color::BLUE);
    booba::APPCONTEXT->bgColor = convertTosColor(Color::WHITE);
    
    Window* cur_window = new Window({WINDOW_WIDTH, WINDOW_HEIGHT});

    StatusBar* statusBar = new StatusBar();
    cur_window->add(statusBar, {0, 0});
    
    ToolsList* tools = new ToolsList();

    tools->connectBy(statusBar, LINKAGE_MODE::TOP, 15, 25);
    tools->toolManager()->linkStatusBar(statusBar);

    statusBar->setPluginCounter(tools->toolManager()->tools().size());

    CanvasManager* canvases = new CanvasManager(tools->toolManager());
    canvases->addCanvas("lol");
    canvases->addCanvas("kek");

    canvases->connectBy(tools, LINKAGE_MODE::RIGHT, 15);

    ColorPicker* col_picker = new ColorPicker();
    cur_window->add(col_picker, {800, 50});

    TopBar* topBar = new TopBar();
    
    cur_window->add(topBar, {0, 0});

    cur_window->exec();

    return 0;
}
