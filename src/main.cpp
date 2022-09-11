#include "drawer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

const uint WINDOW_HEIGHT = 720;
const uint WINDOW_WIDTH  = 1080;

const uint N_X_GRAPHS = 11;
const uint N_Y_GRAPHS = 12;

const uint N_X_SIZE = WINDOW_WIDTH / N_X_GRAPHS;
const uint N_Y_SIZE = WINDOW_HEIGHT / N_Y_GRAPHS;

int main(int argc, char *argv[]){

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "graphics");

    CoordinateSus ct_sus_big(10, 500, 500, 10, -10, 30, -10, 10);
    CoordinateSus ct_sus_mini(420, 500, 500, 420, -10, 10, -10, 10);

    while(window.isOpen()){

        sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
            }
		}

        window.clear();
/*
        for(uint n_y_graphic = 0; n_y_graphic < N_Y_GRAPHS; n_y_graphic++){
            for(uint n_x_graphic = 0; n_x_graphic <  N_X_GRAPHS; n_x_graphic++){

            CoordinateSus ct_sus(n_x_graphic * N_X_SIZE, (n_x_graphic + 1) * N_X_SIZE,
                                    (n_y_graphic + 1) * N_Y_SIZE, n_y_graphic * N_Y_SIZE,
                                    -10, 10, -10, 10);
            DrawGraphic(&window, &ct_sus);                    
            }
        }
*/
        DrawGraphic(&window, &ct_sus_big);
        DrawGraphic(&window, &ct_sus_mini);
        
        window.display();
    }
    return 0;
}
