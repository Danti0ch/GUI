#include "drawer.h"
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>

const uint WINDOW_HEIGHT = 720;
const uint WINDOW_WIDTH  = 1080;

const uint N_X_GRAPHS = 11;
const uint N_Y_GRAPHS = 12;

const uint N_X_SIZE = WINDOW_WIDTH / N_X_GRAPHS;
const uint N_Y_SIZE = WINDOW_HEIGHT / N_Y_GRAPHS;

// TODO: fix arrow offsets
// TODO: логирование
// TODO: какие функции делать внешними а какие методами??
int main(int argc, char *argv[]){

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "graphics");

    // TODO: fix y coords strange
    //CoordinateSus ct_sus_big(10, 500, 500, 10, -10, 10, -10, 10);
    //CoordinateSus ct_sus_mini(420, 500, 500, 420, -10, 10, -10, 10);

    CoordinateSus cts1(10, 210, 210, 10, -10, 10, -10, 10);

    int is_cts1_pressed = 0;
    int cts1_ct_x      = 0, cts1_ct_y = 0;

    while(window.isOpen()){

        sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
            }
            else if(event.type == sf::Event::MouseButtonPressed){

                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;
                
                if(mouseX < cts1.x_upper_pixel() && mouseX > cts1.x_lower_pixel() &&
                   mouseY < cts1.y_lower_pixel() && mouseY > cts1.y_upper_pixel()){
                    
                    is_cts1_pressed = 1;

                    cts1_ct_x = cts1.CountAxisPosX(mouseX);
                    cts1_ct_y = cts1.CountAxisPosY(mouseY);
                }
            }
		}
        window.clear();
        cts1.Draw(&window);

        if(is_cts1_pressed){

            Vector a(cts1_ct_x, cts1_ct_y, VT_DATA::COORD);
            a.Draw(&window, &cts1);
        }

        window.display();
    }
    return 0;
}

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
//        DrawGraphic(&window, &ct_sus_big);
  //      DrawGraphic(&window, &ct_sus_mini);
