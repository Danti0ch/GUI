#include "ToolManager.h"
#include <filesystem>
#include "logger.h"
#include "EventWrapper.h"

ToolManager::ToolManager():
    tools_(),
    p_active_tool_(NULL)
{}

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
            is_updated = true;
        }
        else{
            EDLOG("Unable to open plugin: %s\n", dlerror());
        }
    }

    return is_updated;
}

void ToolManager::apply(stImage* img, const Event* event){
    NASSERT(event);

    if(p_active_tool_ == NULL) return;

    p_active_tool_->apply(img, convertToStandartEvent(event));
    return;
}

void ToolManager::setActiveTool(booba::Tool* new_active_tool){

    if(!checkToolExists(new_active_tool)) return;

    p_active_tool_ = new_active_tool;
    return;
}

Tool* ToolManager::getActiveTool(){
    return p_active_tool_;
}

bool ToolManager::checkToolExists(const Tool* tool){
    for(uint n_tool = 0; n_tool < tools_.size(); n_tool++){
        if(tools_[n_tool].p == tool) return true;
    }

    return false;
}

bool ToolManager::checkToolExists(const std::string& tool_name){
    for(uint n_tool = 0; n_tool < tools_.size(); n_tool++){
        if(tools_[n_tool].p == tool) return true;
    }

    return false;
}
