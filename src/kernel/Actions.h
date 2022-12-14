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
    FuncAction(T_FUNC pFunc):
        pFunc_(pFunc)
    {}
    ~FuncAction() = default;

    void execute() override{
        this->pFunc_();
    }
private:
    T_FUNC pFunc_;
};

// TODO: rename :|
template<typename T_FUNC, typename T_ARG>
class FuncArgAction : public Action{
public:
    FuncArgAction(T_FUNC pFunc, T_ARG arg):
        pFunc_(pFunc), arg_(arg)
    {}

    ~FuncArgAction() = default;

    void execute() override{
        pFunc_(arg_);
    }
private:
    T_FUNC pFunc_;
    T_ARG arg_;
};

template<class T_RECEIVER>
class ObjAction : public Action{
    typedef void (T_RECEIVER::* tMethod)();
public:
    ObjAction(T_RECEIVER* pReceiver, tMethod pFunc):
        pReceiver_(pReceiver),
        pFunc_(pFunc)
    {}

    ~ObjAction() = default;

    void execute() override{
        (pReceiver_->*pFunc_)();
    }
private:
    T_RECEIVER* pReceiver_;
    tMethod pFunc_;
};

template<class T_RECEIVER, typename T_ARG>
class ObjArgAction : public Action{
    typedef void (T_RECEIVER::* tMethod)(T_ARG);
public:
    ObjArgAction(T_RECEIVER* pReceiver, tMethod pFunc, T_ARG arg):
        pReceiver_(pReceiver),
        pFunc_(pFunc),
        arg_(arg)
    {}

    ~ObjArgAction() = default;

    void execute() override{
        (pReceiver_->*pFunc_)(arg_);
    }
private:
    T_RECEIVER* pReceiver_;
    tMethod pFunc_;
    T_ARG arg_;
};

template<class T_RECEIVER, typename T_ARG>
class ObjDynamicArgAction : public Action{
    typedef void (T_RECEIVER::* tMethod)(T_ARG);
public:
    ObjDynamicArgAction(T_RECEIVER* pReceiver, tMethod pFunc, const T_ARG* arg):
        pReceiver_(pReceiver),
        pFunc_(pFunc),
        arg_(arg)
    {}

    ~ObjDynamicArgAction() = default;

    void execute() override{
        (pReceiver_->*pFunc_)(*arg_);
    }

private:
    T_RECEIVER* pReceiver_;
    tMethod pFunc_;
    const T_ARG* arg_;
};
#endif // ACTIONS_H
