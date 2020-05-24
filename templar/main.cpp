#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "entity.h"
#include "player_class.h"
#include "platform_class.h"

const unsigned window_width = 1000;
const unsigned window_height = 700;

float acceleration = 0.2f;
float max_gravity = 5.f;

int main(){

    sf::RenderWindow window(sf::VideoMode( window_width, window_height), "The Templar");
    window.setFramerateLimit(60);

    bool key_w, key_s , key_a, key_d = false;

    sf::Texture player_tex;
    sf::Texture platforms_tex;
    sf::Texture de_castle;
    player_tex.loadFromFile("assets/Images/the_templar_v2.png");
    platforms_tex.loadFromFile("assets/Images/blocks_textures.png");
    de_castle.loadFromFile("assets/Images/de_castle.png");
    sf::Sprite de_castle_sprite(de_castle);

    Player_class player(100.f, 100.f, 129.f, 138.f, player_tex);

    int level_array[10][10] = {{0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0},
                               {0,1,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,1,0,1,0,0,0,0},
                               {0,0,0,0,0,0,0,0,0,0},
                               {0,0,0,0,0,0,0,0,1,0},
                               {0,0,0,0,0,0,0,0,0,0},
                               {0,1,1,1,1,1,1,0,0,0}
                              };

    std::vector<Platform_class> level;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){    //j*50, i*50
            if(level_array[i][j] == 1){
                Platform_class plats(j * 50,i * 50, 48, 48,platforms_tex);
                level.emplace_back(plats);
            }
        }
    }

    sf::View view(sf::Vector2f(0.f,0.f), sf::Vector2f(window_width,window_height));

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        key_w = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        key_s = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        key_a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        key_d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        //player update

        player.update(key_w, key_s , key_a, key_d, level);

        //camera
        view.setCenter(sf::Vector2f(player.getPosition().x + (player.size.x / 2.f), player.getPosition().y + (player.size.y / 2.f)));
        window.setView(view);

        window.clear(sf::Color::Black);

        //drawing on screen
        window.draw(de_castle_sprite);
        window.draw(player);

        for(auto &a : level){
            window.draw(a);
        }

        window.display();
    }

    return 0;
}
