#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <vector>
#include "entity.h"
#include "player_class.h"
#include "platform_class.h"
#include "map_class.h"
#include "enemy_class.h"
#include "coin_class.h"

const unsigned window_width = 1000;
const unsigned window_height = 700;

float acceleration = 0.2f;
float max_gravity = 5.f;

std::vector<Platform_class> level;
std::vector<Enemy_class> enemies;
std::vector<Coin_class> coins;

int main(){

    sf::RenderWindow window(sf::VideoMode( window_width, window_height), "The Templar");
    window.setFramerateLimit(60);

    bool key_space, key_a, key_d, mouse_left = false;
    bool enter = true;

    //music
    sf::Music music;
    music.openFromFile("assets/Music/Dungeon_01.ogg");
    music.setLoop(true);
    music.setVolume(20.f);
    music.play();

    //sounds

    sf::SoundBuffer buffer2, buffer3, buffer4;

    buffer2.loadFromFile("assets/Sounds/die1.wav");
    buffer3.loadFromFile("assets/Sounds/sword-unsheathe.wav");
    buffer4.loadFromFile("assets/Sounds/Coins_Single_04.wav");

    sf::Sound enemy_death(buffer2);
    sf::Sound sword_fight(buffer3);
    sf::Sound coin_collected(buffer4);

    enemy_death.setVolume(40.f);
    sword_fight.setVolume(10.f);
    coin_collected.setVolume(20.f);

    //tex, sprites
    sf::Texture player_tex;
    sf::Texture de_castle;
    sf::Texture enemy_tex;
    sf::Texture coin_tex;
    sf::Texture title_tex, you_won_tex, you_died_tex;
    sf::Texture lives_tex;

    player_tex.loadFromFile("assets/Images/the_templar_sheet_complete.png");
    de_castle.loadFromFile("assets/Images/de_castle.png");
    enemy_tex.loadFromFile("assets/Images/arab_sheet.png");
    coin_tex.loadFromFile("assets/Images/coin.png");
    title_tex.loadFromFile("assets/Images/Title_screen.png");
    you_won_tex.loadFromFile("assets/Images/you_won.png");
    you_died_tex.loadFromFile("assets/Images/you_died.png");
    lives_tex.loadFromFile("assets/Images/lives.png");

    sf::Sprite de_castle_sprite(de_castle), title_screen(title_tex), you_won(you_won_tex), you_died(you_died_tex), lives_sprite(lives_tex);;
    de_castle_sprite.setScale(sf::Vector2f(1.5f, 1.5f));

    //objects

    Player_class player(100.f, 1000.f, 143.f, 151.f, player_tex);

    Map_class map;
    map.draw_map();

    Enemy_class enemy1(100.f, 150.f, 150.f, 150.f, enemy_tex);
    Enemy_class enemy2(630.f, 900.f, 150.f, 150.f, enemy_tex);
    Enemy_class enemy3(1300.f, 150.f, 150.f, 150.f, enemy_tex);
    Enemy_class enemy4(650.f, 50.f, 150.f, 150.f, enemy_tex);
    Enemy_class enemy5(230.f, 450.f, 150.f, 150.f, enemy_tex);

    enemies.emplace_back(enemy1);
    enemies.emplace_back(enemy2);
    enemies.emplace_back(enemy3);
    enemies.emplace_back(enemy4);
    enemies.emplace_back(enemy5);

    //views
    sf::View view(sf::Vector2f(0.f,0.f), sf::Vector2f(700.f, 500.f));
    sf::View view2(sf::Vector2f(500.f, 350.f), sf::Vector2f(1000.f, 700.f));

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
               if (event.mouseButton.button == sf::Mouse::Left){
                    mouse_left = true;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased){
                if (event.mouseButton.button == sf::Mouse::Left)
                    mouse_left = false;
            }
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Enter){
                    enter = false;
                }
            }
        }
        key_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        key_a = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        key_d = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

        //player update
        player.update(key_space, key_a, key_d, mouse_left, level, lives_sprite);

        //enemy attacks
        for(auto &a : enemies)
        a.attack_player(player, enemy_death, sword_fight);

        //coins
        for(auto &a : coins)
        a.collected(player, coin_collected);

        window.clear(sf::Color(33, 159, 179));

        //camera
        if(!enter){
            view.setCenter(sf::Vector2f(player.getPosition().x + (player.size.x / 2.f), player.getPosition().y + (player.size.y / 2.f)));
            window.setView(view);
        }

        //drawing on screen
        window.draw(de_castle_sprite);

        //drawing player
        if(player.health > 0){
            window.draw(player);

        }
        //drawing enemies
        for(auto &b :enemies){
            if(b.enemy_health >0)
                window.draw(b);
        }
        //drawing platforms
        for(auto &a : level){
            window.draw(a);
        }

        //drawing coins
        for(auto &b : coins){
            if(!b.collected_){
                window.draw(b);
            }
            //drawing win screen
            if(std::all_of(coins.begin(), coins.end(), [](Coin_class &coin){
                                                    return coin.collected_;})){

                window.setView(view2);
                window.draw(you_won);
            }
        }

        //drawing hp
        window.draw(lives_sprite);

        //drawing lose screen
        if(player.health <= 0){
            window.setView(view2);
            window.draw(you_died);
        }
        //drawing title screen
        if(enter == true)
            window.draw(title_screen);

        window.display();
    }

    return 0;
}
