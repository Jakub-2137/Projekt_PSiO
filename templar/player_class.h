#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
#include "platform_class.h"


class Player_class : public Entity{
private:
    float speed;
    bool collision, on_ground;
    float jump_height;
public:
    Player_class(float x, float y, float w, float h, sf::Texture &tex);
    void update(bool &key_w, bool &key_s, bool &key_a, bool &key_d, std::vector<Platform_class> &level);
    void collide(float x_vel, float y_vel, std::vector<Platform_class> &level);
};

#endif // PLAYER_CLASS_H
