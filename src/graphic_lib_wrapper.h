#ifndef GL_WRAPPER
#define GL_WRAPPER

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

namespace gl
{
#define Window sf::RenderWindow
#define Color sf::Color
#define Vertex sf::Vertex

Vertex VertexCtor(int x, int y, Color col);
uint GetWindowXSize(Window& window);
uint GetWindowYSize(Window& window);
void DrawVertex(Window* window, Vertex& pixels, uint n_pixels);
void DrawLine(Window* window, double x1, double y1, double x2, double y2, Color col);
#endif // GL_WRAPPER

// TODO: функция process events, wrapper для событий
