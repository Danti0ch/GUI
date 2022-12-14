#ifndef EVENT_WRAPPER_H
#define EVENT_WRAPPER_H

#include "tools.hpp"
#include "graphicImp.h"
#include "Event.h"
#include "CanvasWidget.h"

class stImage : public booba::Image{
public:
    stImage(CanvasWidget* canvas);
    stImage(DrawableArea* area);
    ~stImage() = default;

    size_t getH() override;

    size_t getW() override;

    uint32_t getPixel(size_t x, size_t y) override;

    void setPixel(size_t x, size_t y, uint32_t color) override;

    static stImage* hiddenLayerWrapper;

    Vector pos() const { return pos_; }
private:
    DrawableArea* pArea_;
    Vector pos_;
};

booba::Event* convertToStandartEvent(stImage* space, const Event* event);

#endif // EVENT_WRAPPER_H
