#include "Actions.h"

MacroAction::MacroAction():
    actions_()
{}

MacroAction::~MacroAction(){
    for(auto action : actions_){
        delete action;
    }
}

void MacroAction::add(Action* action){
    actions_.push_back(action);
}

void MacroAction::remove(Action* action){
    actions_.remove(action);
}

void MacroAction::execute(){
    
    std::list<Action*>::iterator iter = actions_.begin();
    for (; iter != actions_.end(); iter++){
        (*iter)->execute();
    }

    return;
}
