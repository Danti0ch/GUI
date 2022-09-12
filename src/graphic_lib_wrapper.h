#ifndef GL_WRAPPER
#define GL_WRAPPER

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace gl
{
typedef sf::RenderWindow Window;
typedef sf::Color        Color;
typedef sf::Vertex       Vertex;

void DrawLine(Window* window, double x1, double y1, double x2, double y2);

InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "graphics"
}

#endif // GL_WRAPPER
