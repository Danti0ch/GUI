#ifndef GL_WRAPPER
#define GL_WRAPPER

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

typedef sf::RenderWindow Window;

void WindowDrawLine(Window* window, double x1, double y1, double x2, double y2);

#endif // GL_WRAPPER