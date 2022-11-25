#include "ToolManager.h"
#include "logger.h"
#include "EventWrapper.h"
#include <dlfcn.h>
#include <filesystem>
#include <iostream>

ToolManager* ToolManager::ACTIVE_TOOL_MANAGER = NULL;
ToolManager::ToolManager():
    tools_(),
    p_active_tool_(NULL)
{
    if(ACTIVE_TOOL_MANAGER == NULL){
        ACTIVE_TOOL_MANAGER = this;
    }
}

ToolManager::~ToolManager(){}

bool ToolManager::updateTools(){
    
    bool is_updated = false;

    for (const auto& file : std::filesystem::directory_iterator(PLAGINS_FOLDER_PATH)) {
        if (file.is_directory()) {
            continue;
        }

        if(checkToolExists(file.path())) continue;

        void* dlHandler = dlopen(file.path().c_str(), RTLD_LAZY);
        
        if(dlHandler) {
            void (*initFunc)()     = NULL;
            *((void**)(&initFunc)) = dlsym(dlHandler, "init_module");

            (*initFunc)();

            // TODO: make checker if symbol is truly loaded

            std::list<ToolWrapper>::iterator tmp_iter = tools_.begin();

            std::advance(tmp_iter, tools_.size() - 1);
            (*tmp_iter).name = file.path();
            is_updated = true;
            MDLOG("Plugin %s opened and loaded", file.path().c_str());
        }
        else{
            EDLOG("Unable to open plugin: %s\n", dlerror());
        }
    }

    return is_updated;
}

void ToolManager::addTool(booba::Tool* p_tool){

    // TODO: refactor

    ToolWrapper wrapper = {p_tool, ""};
    
    tools_.push_back(wrapper);

    return;
}

void ToolManager::apply(stImage* space, const Event* event){
    NASSERT(event);

    if(p_active_tool_ == NULL) return;

    p_active_tool_->apply(space, convertToStandartEvent(space, event));
    return;
}

/*
void ToolManager::setActiveTool(const booba::Tool* new_active_tool){

    std::list<ToolWrapper>::const_iterator tools_iter;

    for (tools_iter = tools_.begin(); tools_iter != tools_.end(); tools_iter++){
        if(tools_iter->p == new_active_tool){
            p_active_tool_ = tools_iter->p;
            return;
        }
    }

    return;
}
*/

void ToolManager::setActiveTool(uint n_tool){

    std::cout << "ok!\n";
    if(n_tool > tools_.size()) return;  
    std::list<ToolWrapper>::iterator new_active_tool = tools_.begin();

    std::advance(new_active_tool, n_tool);
    p_active_tool_ = new_active_tool->p;
    return;
}

booba::Tool* ToolManager::getActiveTool(){
    return p_active_tool_;
}

bool ToolManager::checkToolExists(const booba::Tool* tool){
    std::list<ToolWrapper>::const_iterator tools_iter;

    for (tools_iter = tools_.begin(); tools_iter != tools_.end(); tools_iter++){
        if(tools_iter->p == tool) return true;
    }

    return false;
}

bool ToolManager::checkToolExists(const std::string& tool_name){
    std::list<ToolWrapper>::const_iterator tools_iter;

    for (tools_iter = tools_.begin(); tools_iter != tools_.end(); tools_iter++){
        if(tools_iter->name == tool_name) return true;
    }

    return false;
}

const std::list<ToolWrapper>& ToolManager::tools() const{
    return tools_;
}
