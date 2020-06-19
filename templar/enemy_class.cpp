#include <SFML/Graphics.hpp>
#include "enemy_class.h"

Enemy_class::Enemy_class(float x_, float y_, float w_, float h_, sf::Texture &tex){

    dead = false;

    enemy_health = 100;

    size.x = w_;
    size.y = h_;

    attack_counter = 0;
    attack_frames = 4;
    attack_speed = 10;
    sound_counter = 1;

    frame_size.x = 150;
    frame_size.y = 150;

    frames_amount.x = tex.getSize().x / frame_size.x;
    frames_amount.y = tex.getSize().y / frame_size.y;

    for(int y = 0; y < frames_amount.y; y++){
        for(int x = 0; x < frames_amount.x; x++){
            sf::IntRect frame(x * frame_size.x, y * frame_size.y, frame_size.x, frame_size.y);
            anim_frames.emplace_back(frame);
        }
    }
    setTextureRect(anim_frames[0]);
    setTexture(tex);
    setPosition(x_,y_);
}

void Enemy_class::attack_player(Player_class &player, sf::Sound &enemy_death, sf::Sound &sword_fight){

    // animacja ataku prawo
    if((getPosition().x + size.x + 50 > player.getPosition().x) &&
       (getPosition().x + 70 < player.getPosition().x) &&
       (getPosition().y - 20 < player.getPosition().y) &&
       (getPosition().y + size.y + 20 > player.getPosition().y + player.size.y)){

        for(int i = 0; i < attack_frames; i++){
            if(attack_counter == (i + 1) * attack_speed){
                setTextureRect(anim_frames[i + 2]);
            }
        }
        if(attack_counter == attack_frames * attack_speed){
            attack_counter = 0;
        }
        attack_counter++;

        //player attacking
        if(player.attacking == true){

            player.got_him = true;

            enemy_health--;

            sound_counter--;

            for(int a = 0; a < 20; a++)
                if(sound_counter == -25*a)
                    sword_fight.play();

        } else if(player.attacking == false){
            player.got_him = false;

        }
        //death
        if(enemy_health == 0){
            dead = true;
            enemy_death.play();
        }
        //player health
        if(!dead){
        player.health--;
        }
    }
    // animacja ataku lewo

    if ((getPosition().x - 50 < player.getPosition().x + player.size.x) &&
        (getPosition().x + 70 > player.getPosition().x) &&
        (getPosition().y - 20 < player.getPosition().y) &&
        (getPosition().y + size.y + 20 > player.getPosition().y + player.size.y)){

        for(int i = 0; i < attack_frames; i++){
            if(attack_counter == (i + 1) * attack_speed){

                 setTextureRect(anim_frames[i + 6]);
            }
        }
        if(attack_counter == attack_frames * attack_speed){
            attack_counter = 0;
        }
        attack_counter++;

        //player attacking
        if(player.attacking == true){

            player.got_him = true;

            enemy_health--; 

            sound_counter--;

            for(int a = 0; a < 20; a++)
                if(sound_counter == -25*a)
                    sword_fight.play();

        } else if(player.attacking == false){

            player.got_him = false;
        }
        //enemy death
        if(enemy_health == 0){
            dead = true;
            enemy_death.play();
        }
        //player health
        if(!dead){
        player.health--;
        }
    }
}









