#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H
#pragma once

#include "entity.h"
#include "player_class.h"

class Enemy_class : public Entity{
private:
    bool collision, dead;
    int attack_frames, attack_speed, attack_counter, sound_counter;
public:
    int enemy_health;
    Enemy_class(float x_, float y_, float w_, float h_, sf::Texture &tex);
    void attack_player(Player_class &player, sf::Sound &enemy_death, sf::Sound &sword_fight);
};

#endif // ENEMY_CLASS_H
