#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "player_class.h"
#include "entity.h"
#include "hitbox.h"
#include "platform_class.h"

extern float acceleration;
extern float max_gravity;

Player_class::Player_class(float x_, float y_, float w_, float h_, sf::Texture &tex){

    size.x = w_;
    size.y = h_;

    jump_height = 7.f;
    speed = 5.f;
    setTexture(tex);
    setPosition(x_,y_);

}

void Player_class::update(bool &key_w, bool &key_s, bool &key_a, bool &key_d, std::vector<Platform_class> &level){

    if(key_w && on_ground) velocity.y = -std::abs(jump_height);
    if(on_ground == false){
        velocity.y += acceleration;
        if(velocity.y > max_gravity)
            velocity.y = max_gravity;
    }
    if(key_a) velocity.x = -1.f;
    if(key_s) velocity.y = 1.f;
    if(key_d) velocity.x = 1.f;
    if(!(key_a || key_d)) velocity.x = 0.f;

    move(velocity.x * speed,0);
    collide(velocity.x, 0.f, level);

    on_ground = false;
    move(0, velocity.y);
    collide(0.f, velocity.y, level);


}

void Player_class::collide(float x_vel, float y_vel, std::vector<Platform_class> &level){
    for(auto &a : level){
        if(getPosition().x + 33.f < a.hitbox.right &&
           getPosition().x + size.x - 33.f > a.hitbox.left &&
           getPosition().y + 0.f < a.hitbox.bottom &&
           getPosition().y + size.y - 1.f > a.hitbox.top)
        {
            collision = true;
        }
        else{
            collision = false;
        }
        if(collision){
            if(x_vel > 0){
                setPosition(a.hitbox.left - size.x + 33.f, getPosition().y);
                velocity.x = 0.f;
            }
            if(x_vel < 0){
                setPosition(a.hitbox.right - 33.f, getPosition().y);
                velocity.x = 0.f;
            }
            if(y_vel > 0){
                setPosition(getPosition().x, a.hitbox.top - size.y + 1.f);
                velocity.y = 0.f;
                on_ground = true;
            }
            if(y_vel < 0){
                setPosition(getPosition().x, a.hitbox.bottom);
                velocity.y = 0.f;

            }
        }
    }
}




