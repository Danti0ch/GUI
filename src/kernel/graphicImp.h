/**
 * @file graphicImp.h
 * @brief file, consisted of system-depended structures and operations that providing non-system depended interface for drawing and containig drawable objects
 * @version 0.1
 * 
 */
#ifndef GRAPHIC_IMP_H
#define GRAPHIC_IMP_H

#include "Auxil.h"
#include "Event.h"
#include "Color.h"
#include <queue>

// TODO: rename
//? should only be in cpu
/**
 * @brief could load images from memory, draw pixels and other stuff
 * 
 */
class DrawableArea{
public:
    virtual ~DrawableArea() = default;

    virtual void drawImage(const std::string& path) = 0;
    virtual void clear(const Color& col) = 0;

    virtual Color getPixel(Vector point) = 0;
    virtual void  setPixel(Vector point, Color col) = 0;

    virtual Vector size() const = 0;
    virtual void transparency(const ProportionRatio& ratio) = 0;
};

// TODO: rename
//? need to implement draw line, draw pixel and etc
//? should only be in gpu
/**
 * @brief could draw on itself primitives like image, set of pixels or text and contain them.
 * 
 */
class RenderObject{
public:
    virtual ~RenderObject() = default;

    virtual void draw(Vector point, const Text& data) = 0;
    virtual void draw(Vector point, const RenderObject* data) = 0;

    /// @brief draws data, that restricted by area rect
    virtual void draw(Vector point, const RenderObject* data, const RectangleArea& area) = 0;

    virtual void draw(Vector point, const DrawableArea* data) = 0;
    virtual void draw(Vector point, const DrawableArea* data, const RectangleArea& area) = 0;
    virtual void clear(const Color& col) = 0;

    virtual Vector size() const = 0;

    virtual void changeFont(const std::string& path) = 0;
};

// TODO: rename
/**
 * @brief interface for opening, closing window on display and extracting event from it
 * 
 */
class RealWindow{
public:
    RealWindow(Vector size, unsigned int extractedEventsQueueMaxSize);
    virtual ~RealWindow() throw();

    virtual void open()  = 0;
    virtual void close() = 0;
    virtual void draw()  = 0;

    virtual Vector size() const = 0;
    virtual bool isOpen() const = 0;

    RenderObject* buffer();
    void extractEvents();
    
protected:
    /// @brief returns 1, if event was extraced an 0 otherwise
    virtual bool extractEvent(Event**) const = 0;
public:
    std::queue<Event*> extractedEvents;
private:
    unsigned int extractedEventsQueueMaxSize_;
    RenderObject* buffer_;

    Vector size_;
};

class GraphicImpFabric{
public:
    virtual ~GraphicImpFabric(){}

    virtual DrawableArea* createDrawableArea(Vector size) const = 0;
    virtual RenderObject* createRenderObject(Vector size) const = 0;
    virtual RealWindow*   createRealWindow(Vector size) const = 0;
};

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

class SfmlDrawableArea : public DrawableArea/*, private sf::Image*/{
public:
    SfmlDrawableArea(Vector size);
    ~SfmlDrawableArea();

    void drawImage(const std::string& path) override;
    void clear(const Color& col) override;

    Color getPixel(Vector point) override;
    void  setPixel(Vector point, Color col) override;

    Vector size() const override;

    const sf::Image* storage() const;
    void transparency(const ProportionRatio& ratio) override;
private:
    sf::Image* storage_;
};

class SfmlRenderObject : public RenderObject{
public:
    SfmlRenderObject(Vector size);
    ~SfmlRenderObject();

    void draw(Vector point, const Text& data) override;
    void draw(Vector point, const RenderObject* data) override;
    void draw(Vector point, const RenderObject* data, const RectangleArea& rect) override;
    void draw(Vector point, const DrawableArea* data) override;
    void draw(Vector point, const DrawableArea* data, const RectangleArea& rect) override;

    void clear(const Color& col) override;

    void changeFont(const std::string& path) override;

    Vector size() const override;
    const sf::RenderTexture* storage() const;
private:
    sf::RenderTexture* storage_;
    sf::Font font_;
private:
    Vector convertPos(Vector pos) const;
};

class SfmlRealWindow : public RealWindow{
public:
    SfmlRealWindow(Vector size);
    ~SfmlRealWindow();

    void open() override;
    void close() override;
    void draw() override;

    Vector size() const override;

    bool isOpen() const override;

private:
    bool extractEvent(Event** storage) const override;

    Vector convertPosToSFML(Vector pos) const;
    Vector convertPosFromSFML(Vector pos) const;
private:
    sf::RenderWindow* storage_;
};

class SfmlGraphicImpFabric : public GraphicImpFabric{
public:
    SfmlGraphicImpFabric();
    ~SfmlGraphicImpFabric();

    DrawableArea* createDrawableArea(Vector size) const override;
    RenderObject* createRenderObject(Vector size) const override;
    RealWindow*   createRealWindow(Vector size)   const override;
};

const GraphicImpFabric* giFabric = &SfmlGraphicImpFabric();

#define CREATE_DRAWABLE_AREA(size) (giFabric->createDrawableArea(size))
#define CREATE_RENDER_OBJECT(size) (giFabric->createRenderObject(size))
#define CREATE_REAL_WINDOW(size) (giFabric->createRealWindow(size))

ManipulatorsContext manipulatorsContext;

#endif // GRAPHIC_IMP_H
