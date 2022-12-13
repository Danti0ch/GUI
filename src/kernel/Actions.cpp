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

template<typename T_FUNC>
FuncAction<T_FUNC>::FuncAction(T_FUNC pFunc):
    pFunc_(pFunc)
{}

template<typename T_FUNC>
void FuncAction<T_FUNC>::execute(){
    pFunc();
}

template<typename T_FUNC, typename T_ARG>
FuncArgAction<T_FUNC, T_ARG>::FuncArgAction(T_FUNC pFunc, T_ARG arg):
    pFunc_(pFunc), arg_(arg)
{}

template<typename T_FUNC, typename T_ARG>
void FuncArgAction<T_FUNC, T_ARG>::execute(){
    pFunc_(arg_);
}
template<class T_RECEIVER, typename T_FUNC>
ObjAction<T_RECEIVER, T_FUNC>::ObjAction(T_RECEIVER* pReceiver, T_FUNC pFunc):
    pReceiver_(pReceiver),
    pFunc_(pFunc)
{}

template<class T_RECEIVER, typename T_FUNC>
void ObjAction<T_RECEIVER, T_FUNC>::execute(){
    (pReceiver_->*pFunc)();
}

template<class T_RECEIVER, typename T_METHOD, typename T_ARG>
ObjArgAction<T_RECEIVER, T_METHOD, T_ARG>::ObjArgAction(T_RECEIVER* pReceiver, T_METHOD pFunc, T_ARG arg):
    pReceiver_(pReceiver),
    pFunc_(pFunc),
    arg_(arg)
{}


template<class T_RECEIVER, typename T_FUNC, typename T_ARG>
void ObjArgAction<T_RECEIVER, T_FUNC, T_ARG>::execute(){
    (pReceiver_->*pFunc)(arg_);
}
