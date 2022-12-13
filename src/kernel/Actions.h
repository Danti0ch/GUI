#ifndef ACTIONS_H
#define ACTIONS_H

#include <list>

class Action{
public:
    virtual ~Action() = default;
    virtual void execute() = 0;
};

class MacroAction : public Action{
public:
    MacroAction();
    ~MacroAction();

    void add(Action* action);
    void remove(Action* action);

    void execute() override;
private:
    std::list<Action*> actions_;
};

template<typename T_FUNC>
class FuncAction : public Action{
public:
    FuncAction(T_FUNC pFunc);
    ~FuncAction() = default;

    void execute() override;
private:
    T_FUNC pFunc_;
};

// TODO: rename :|
template<typename T_FUNC, typename T_ARG>
class FuncArgAction : public Action{
public:
    FuncArgAction(T_FUNC pFunc, T_ARG arg);
    ~FuncArgAction() = default;

    void execute() override;
private:
    T_FUNC pFunc_;
    T_ARG arg_;
};

template<class T_RECEIVER, typename T_METHOD>
class ObjAction : public Action{
public:
    ObjAction(T_RECEIVER* pReceiver, T_METHOD pFunc);
    ~ObjAction() = default;

    void execute() override;
private:
    T_RECEIVER* pReceiver_;
    T_FUNC pFunc_;
};

template<class T_RECEIVER, typename T_METHOD, typename T_ARG>
class ObjArgAction : public Action{
public:
    ObjArgAction(T_RECEIVER* pReceiver, T_METHOD pFunc, T_ARG arg);
    ~ObjArgAction() = default;

    void execute() override;
private:
    T_RECEIVER* pReceiver_;
    T_FUNC pFunc_;
    T_ARG arg_;
};

#endif // ACTIONS_H
