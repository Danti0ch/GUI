#pragma once

#include <cmath>
#include <stack>
#include <chrono>
#include <cstdio>

#include "tools.hpp"

const char DotTexture[]   = "./Icons/min/Dot.png";

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
