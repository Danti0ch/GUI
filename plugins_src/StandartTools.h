#pragma once

#include <cmath>
#include <stack>
#include <chrono>
#include <cstdio>

#include "tools.hpp"
#include "Text.h"

const char DotTexture[]   = "./Icons/min/Dot.png";

#define TOOL_INIT(TOOL_TYPE)            \
extern "C" void booba::init_module() {   \
    TOOL_TYPE* tool = new TOOL_TYPE();    \
    booba::addTool(tool);                  \
}

struct CordsPair {
    int32_t x;
    int32_t y;
};

int64_t GetTimeMiliseconds();

class AbstractTool : public booba::Tool {
public:
    AbstractTool(){}

    virtual ~AbstractTool() {}

    virtual const char* getTexture() override {
        return NULL;
    }
};

class DotTool : public AbstractTool {
public:
    DotTool() :
    AbstractTool()
    {}

    virtual ~DotTool() {}

    virtual void apply(booba::Image* image, const booba::Event* event) override;
    virtual void buildSetupWidget() override {}
};

class PenTool : public AbstractTool {
public:
    PenTool();

    virtual ~PenTool() {}

    virtual void apply(booba::Image* image, const booba::Event* event) override;
    virtual void buildSetupWidget() override {}
private:
    bool isLButtonPressed;
    uint prevX, prevY;

    uint pen_size_;
};

class TextInsertTool : public AbstractTool{
public:
    TextInsertTool();

    virtual ~TextInsertTool() {}

    virtual void apply(booba::Image* image, const booba::Event* event) override;
    virtual void buildSetupWidget() override {}
private:
    Text data_;
};

class PiptTool : public AbstractTool{
public:
    PiptTool();

    virtual ~PiptTool() {}

    virtual void apply(booba::Image* image, const booba::Event* event) override;
    virtual void buildSetupWidget() override {}
};

class PixBuff;

class AreaSelectionTool : public AbstractTool{
public:
    AreaSelectionTool();
    
    virtual ~AreaSelectionTool() {}

    virtual void apply(booba::Image* image, const booba::Event* event) override;
    virtual void buildSetupWidget() override {}
private:
    PixBuff* buff_;
    uint64_t canvas_id_;

    uint area_width_, area_height_;
    uint x_, y_;
};
