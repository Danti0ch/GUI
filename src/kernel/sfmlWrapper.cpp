#include "graphicImp.h"
#include "logger.h"

const int EXTRACTED_EVENT_QUEUE_MAX_SIZE = 16;

SfmlRenderObject::SfmlRenderObject(Vector size):
    storage_(new sf::RenderTexture()),
    font_()
{
    storage_->create(size.x, size.y);

    // TODO: fix
    font_.loadFromFile("../fonts/arial.ttf");
}

SfmlRenderObject::~SfmlRenderObject(){
    delete storage_;
}

void SfmlRenderObject::drawText(Vector point, const Text& data){
    sf::Text text_obj(data.str, font_, data.font_size);
        
    Vector real_point = convertPos(point);

    text_obj.setPosition(real_point.x, real_point.y - data.font_size + 2);
    text_obj.setFillColor(converColorToLib(data.col));

    storage_->draw(text_obj);
    storage_->display();

    return;
}

void SfmlRenderObject::draw(Vector point, const RenderObject* data){

    const SfmlRenderObject* casted_data = reinterpret_cast<const SfmlRenderObject*>(data);
    Vector real_point = convertPos(point);

    sf::Sprite tmp_sprite(casted_data->storage_->getTexture()); 
    tmp_sprite.setPosition(sf::Vector2f(real_point.x, real_point.y - data->size().y));
    storage_->draw(tmp_sprite);
    storage_->display();
    
    return;
}

void SfmlRenderObject::draw(Vector point, const RenderObject* data, const RectangleArea& rect){

    const SfmlRenderObject* casted_data = reinterpret_cast<const SfmlRenderObject*>(data);

    Vector real_point = convertPos(point);

    sf::Sprite tmp_sprite(casted_data->storage_->getTexture(), sf::IntRect(casted_data->convertPos(rect.pos).x, casted_data->convertPos(rect.pos).y - rect.size.y, rect.size.x, rect.size.y)); 
    tmp_sprite.setPosition(sf::Vector2f(real_point.x, real_point.y - rect.size.y));
    storage_->draw(tmp_sprite);
    storage_->display();

    return;
}

void SfmlRenderObject::draw(Vector point, const DrawableArea* data){

    const SfmlDrawableArea* casted_data = reinterpret_cast<const SfmlDrawableArea*>(data);

    sf::Texture tmp_texture;
    tmp_texture.loadFromImage(*casted_data->storage());

    Vector real_point = convertPos(point);
    sf::Sprite tmp_sprite(tmp_texture); 

    tmp_sprite.setPosition(sf::Vector2f(real_point.x, real_point.y - data->size().y));
    storage_->draw(tmp_sprite);
    storage_->display();

    return;
}

void SfmlRenderObject::draw(Vector point, const DrawableArea* data, const RectangleArea& rect){

    const SfmlDrawableArea* casted_data = reinterpret_cast<const SfmlDrawableArea*>(data);

    sf::Texture tmp_texture;
    tmp_texture.loadFromImage(*casted_data->storage());

    Vector real_point = convertPos(point);
    sf::Sprite tmp_sprite(tmp_texture, sf::IntRect(rect.pos.x, rect.pos.y - rect.size.y, rect.size.x, rect.size.y)); 
    
    tmp_sprite.setPosition(sf::Vector2f(real_point.x, real_point.y - rect.size.y));
    storage_->draw(tmp_sprite); 
    storage_->display();
}

void SfmlRenderObject::clear(const Color& col){

    storage_->clear(converColorToLib(col));
    return;
}

Vector SfmlRenderObject::size()  const { 
    //MDLOG("%u, %u", storage_->getSize().x, storage_->getSize().y)
    return Vector(storage_->getSize().x, storage_->getSize().y); }

Vector SfmlRenderObject::getTextSize(const Text& text){

    sf::Text text_obj(text.str, font_, text.font_size);

    sf::FloatRect bounds = text_obj.getLocalBounds();
    return Vector(bounds.width, bounds.height);
}

const sf::RenderTexture* SfmlRenderObject::storage() const{ return storage_; }


SfmlDrawableArea::SfmlDrawableArea(Vector size):
    storage_(new sf::Image())
{
    storage_->create(size.x, size.y, converColorToLib(Color::WHITE));
}

SfmlDrawableArea::~SfmlDrawableArea(){}

void SfmlDrawableArea::drawImage(Vector size, const std::string& path){

    storage_->create(size.x, size.y);

    return;
}

void SfmlDrawableArea::clear(const Color& col){

    for(uint y = 0; y < storage_->getSize().y; y++){
        for(uint x = 0; x < storage_->getSize().x; x++){
            storage_->setPixel(x, y, converColorToLib(col));
        }
    }

    return;
}

Color SfmlDrawableArea::getPixel(Vector point){
    Vector realPoint = convertPos(point);
    return convertColorFromLib(storage_->getPixel(realPoint.x, realPoint.y));
}

void SfmlDrawableArea::setPixel(Vector point, Color col){
    Vector realPoint = convertPos(point);
    storage_->setPixel(realPoint.x, realPoint.y, converColorToLib(col));
    return;
}

Vector SfmlDrawableArea::convertPos(Vector pos) const{
    return Vector(pos.x, size().y - pos.y);
}

Vector SfmlDrawableArea::size() const { return Vector(storage_->getSize().x, storage_->getSize().y); }

void SfmlDrawableArea::transparency(const ProportionRatio& ratio){

    for(uint y = 0; y < storage_->getSize().y; y++){
        for(uint x = 0; x < storage_->getSize().x; x++){
            sf::Color color = storage_->getPixel(x, y);
            color.a = 255 * ratio;

            storage_->setPixel(x, y, color);
        }
    }

    return;
}

const sf::Image* SfmlDrawableArea::storage() const { return storage_; }

SfmlRealWindow::SfmlRealWindow(Vector size):
    RealWindow(size, EXTRACTED_EVENT_QUEUE_MAX_SIZE),
    storage_(new sf::RenderWindow(sf::VideoMode(size.x, size.y), "404"))
{
    buffer_ = new SfmlRenderObject(size);
}

SfmlRealWindow::~SfmlRealWindow(){
    delete buffer_;
}
void SfmlRealWindow::open(){

    if(isOpen()) return;
    storage_->create(sf::VideoMode(size().x, size().y), "404");
    return;
}

void SfmlRealWindow::close(){
    if(!isOpen()) return;
    
    storage_->close();
    return;
}

void SfmlRealWindow::draw(){

    sf::Sprite tmp_sprite(reinterpret_cast<const SfmlRenderObject*>(buffer())->storage()->getTexture()); 
    storage_->draw(tmp_sprite);

    storage_->display();

    return;
}

// TODO: maybe we should storage size vals
Vector SfmlRealWindow::size() const  { return Vector(storage_->getSize().x, storage_->getSize().y); }
 
bool SfmlRealWindow::isOpen() const { return storage_->isOpen(); }

bool SfmlRealWindow::extractEvent(Event** storage) const{
    
    sf::Event sf_event;

    if(!storage_->pollEvent(sf_event)) return false;

    // TODO:
    //if(sf_event.type == sf::Event::Closed){
    //    *p_event = new CloseButtonPressedEvent();
    //}

    if(sf_event.type == sf::Event::MouseButtonPressed || sf_event.type == sf::Event::MouseMoved || sf_event.type == sf::Event::MouseButtonReleased){

        if(sf_event.type == sf::Event::MouseButtonPressed){
            if(sf_event.mouseButton.button == sf::Mouse::Right){
                *storage = new MouseButtonPressedEvent(T_MOUSE_BUTTON::R);
            }
            else{
                *storage = new MouseButtonPressedEvent(T_MOUSE_BUTTON::L);
            }
        }
        else if(sf_event.type == sf::Event::MouseButtonReleased){
            if(sf_event.mouseButton.button == sf::Mouse::Right){
                *storage = new MouseButtonReleasedEvent(T_MOUSE_BUTTON::R);
            }
            else{
                *storage = new MouseButtonReleasedEvent(T_MOUSE_BUTTON::L);
            }
        }
        else if(sf_event.type == sf::Event::MouseMoved){
            //MDLOG("(%u, %u)----->(%u, %u)", sf_event.mouseMove.x, sf_event.mouseMove.y, ManipulatorsContext::activeContext.mousePos().x, ManipulatorsContext::activeContext.mousePos().y);
            *storage = new MouseMovedEvent(convertPosFromSFML(Vector(sf_event.mouseMove.x, sf_event.mouseMove.y)), ManipulatorsContext::activeContext.mousePos());
        }
    }
    else if(sf_event.type == sf::Event::KeyPressed){
        *storage = new KeyPressedEvent(static_cast<T_KEY>(sf_event.key.code));
    }
    else if(sf_event.type == sf::Event::KeyReleased){
        *storage = new KeyReleasedEvent(static_cast<T_KEY>(sf_event.key.code));
    }
    else if(sf_event.type == sf::Event::MouseWheelScrolled){
        *storage = new MouseWheelScrolledEvent(sf_event.mouseWheelScroll.delta);
    }
    else return false;
    return true;
}

Vector SfmlRealWindow::convertPosToSFML(Vector pos) const{
    return Vector(pos.x, size().y - pos.y);
}

Vector SfmlRealWindow::convertPosFromSFML(Vector pos) const{
    return Vector(pos.x, size().y - pos.y);
}

void SfmlRenderObject::changeFont(const std::string& path){
    font_.loadFromFile(path);

    return;
}

Vector SfmlRenderObject::convertPos(Vector pos) const{
    return Vector(pos.x, size().y - pos.y);
}

SfmlGraphicImpFabric::SfmlGraphicImpFabric(){}
SfmlGraphicImpFabric::~SfmlGraphicImpFabric(){}

DrawableArea* SfmlGraphicImpFabric::createDrawableArea(Vector size) const {
    return new SfmlDrawableArea(size);
}

RenderObject* SfmlGraphicImpFabric::createRenderObject(Vector size) const {
    return new SfmlRenderObject(size);
}

RealWindow* SfmlGraphicImpFabric::createRealWindow(Vector size) const{
    return new SfmlRealWindow(size);
}

SfmlGraphicImpFabric fabric;
GraphicImpFabric* GraphicImpFabric::active_fabric = &fabric;

sf::Color converColorToLib(const Color& col){
    sf::Color sf_col(col.r(), col.g(), col.b(), col.a());
    return sf_col;
}

Color convertColorFromLib(const sf::Color& sf_col){
    Color col(sf_col.r, sf_col.g, sf_col.b, sf_col.a);
    return col;
}
