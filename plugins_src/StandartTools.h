#pragma once

#include <cmath>
#include <stack>
#include <chrono>
#include <cstdio>
#include "logger.h"

#include "tools.hpp"
#include "optionals.hpp"
#include "Auxil.h"

// TODO: разные ашники
#define TOOL_INIT(TOOL_TYPE)            \
extern "C" void booba::init_module() {   \
    TOOL_TYPE* tool = new TOOL_TYPE();    \
    booba::addTool(tool);                  \
}

struct CordsPair {
    int32_t x;
    int32_t y;
};

class AbstractTool : public booba::Tool {
public:
    AbstractTool(){}

    virtual ~AbstractTool() {}

    virtual const char* getTexture() override {
        return NULL;
    }
};

#include "string.h"

extern booba::ApplicationContext* booba::APPCONTEXT;

// https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%98%D0%BD%D1%82%D0%B5%D1%80%D0%BF%D0%BE%D0%BB%D1%8F%D1%86%D0%B8%D1%8F/%D0%9C%D0%BD%D0%BE%D0%B3%D0%BE%D1%87%D0%BB%D0%B5%D0%BD_%D0%9B%D0%B0%D0%B3%D1%80%D0%B0%D0%BD%D0%B6%D0%B0
class LagrangePolynom{
public:
    LagrangePolynom():
        cur_pos_(0), size_(4), n_points_initiated_(0)
    {
        x_ = new double[size_];
        y_ = new double[size_];   

        memset(x_, 0, size_ * sizeof(double));
        memset(y_, 0, size_ * sizeof(double)); 
    }

    ~LagrangePolynom(){
        delete[] x_;
        delete[] y_;
    }

    void add(uint x, uint y){
        if(cur_pos_ + 1 == size_){
            cur_pos_ = 0;
        }
        else cur_pos_++;

        x_[cur_pos_] = (double)x;
        y_[cur_pos_] = (double)y;

        n_points_initiated_ = std::min(size_, n_points_initiated_ + 1);
    }

    double interpolate(double x){
        
        assert(n_points_initiated_ >= 2);

        double lagrange_pol = 0;    
        double basics_pol;

        uint n_points_handled = 0;

        for (int i = cur_pos_ + 1; i < size_ && n_points_handled < n_points_initiated_; i++, n_points_handled++){
            basics_pol = 1;

            uint n_sub_points_handled = 0;
            for (int j = cur_pos_ + 1; j < size_ && n_sub_points_handled < n_points_initiated_; j++, n_sub_points_handled++){
                if (j == i) continue;
                basics_pol *= (x - x_[j])/(x_[i] - x_[j]);		
            }
            for (int j = 0; j <= cur_pos_ && n_sub_points_handled < n_points_initiated_; j++, n_sub_points_handled++){
                if (j == i) continue;
                basics_pol *= (x - x_[j])/(x_[i] - x_[j]);		
            }
            lagrange_pol += basics_pol*y_[i];
        }
        for (int i = 0; i <= cur_pos_ && n_points_handled < n_points_initiated_; i++, n_points_handled++){
            basics_pol = 1;

            uint n_sub_points_handled = 0;
            for (int j = cur_pos_ + 1; j < size_ && n_sub_points_handled < n_points_initiated_; j++, n_sub_points_handled++){
                if (j == i) continue;
                basics_pol *= (x - x_[j])/(x_[i] - x_[j]);		
            }
            for (int j = 0; j <= cur_pos_ && n_sub_points_handled < n_points_initiated_; j++, n_sub_points_handled++){
                if (j == i) continue;
                basics_pol *= (x - x_[j])/(x_[i] - x_[j]);		
            }
            lagrange_pol += basics_pol*y_[i];
        }

        return lagrange_pol;
    }

    void reset(){
        cur_pos_ = 0;
        memset(x_, 0, size_ * sizeof(double));
        memset(y_, 0, size_ * sizeof(double)); 
        return;
    }

    bool is_empty(){
        return n_points_initiated_ == 0;
    }

private:
    double* x_;
    double* y_;

    uint size_;
    uint cur_pos_;
    uint n_points_initiated_;
};

class PenTool : public AbstractTool {
public:
    PenTool();

    virtual ~PenTool() {}

    virtual void apply(booba::Image* image, const booba::Event* event) override;
    virtual void buildSetupWidget() override;

    const char* getTexture() override;
private:
    bool isLButtonPressed, isRButtonPressed;

    LagrangePolynom polynom_;
    int pen_size_;

    Vector lastPos_;
    uint64_t sizeControllerScrollBar_;
private:
    void draw_dot(booba::Image* image, int x, int y);
    void draw_line(booba::Image* image, uint xF, uint xS);
    void draw_vert_line(booba::Image* image, uint x, uint yF, uint yS);
};

class PixBuff;

class AreaSelectionTool : public AbstractTool{
public:
    AreaSelectionTool();
    
    virtual ~AreaSelectionTool() {}

    virtual void apply(booba::Image* image, const booba::Event* event) override;
    virtual void buildSetupWidget() override {}

    const char* getTexture() override;
private:
    PixBuff* buff_;
    uint64_t canvas_id_;

    uint area_width_, area_height_;
    uint x_, y_;

    bool isMouseClicked_;
};
