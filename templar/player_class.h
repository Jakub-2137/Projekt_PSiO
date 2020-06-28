#ifndef PLAYER_CLASS_H
#define PLAYER_CLASS_H
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "entity.h"
#include "platform_class.h"

class Player_class : public Entity{
private:
    float speed;
    bool collision, on_ground, face_right, dead;
    float jump_height;
    int walk_counter, repose_counter, attack_counter, walk_frames,
    repose_frames, attack_frames, walk_speed, repose_speed, attack_speed;

public:
    int health;
    bool attacking, got_him;
    sf::Sprite lives_sprite;
    Player_class(float x, float y, float w, float h, sf::Texture &tex);
    void update(bool &key_space, bool &key_a, bool &key_d, bool &mouse_left, std::vector<Platform_class> &level, sf::Sprite &lives_sprite);
    void collide(float x_vel, float y_vel, std::vector<Platform_class> &level);
    void animate(bool &mouse_left);
    void walk();
    void repose();
    void attack(bool &mouse_left);
    void show_lives(Sprite &lives_sprite);
};

#endif // PLAYER_CLASS_H
