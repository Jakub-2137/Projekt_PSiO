#ifndef COIN_CLASS_H
#define COIN_CLASS_H
#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player_class.h"

class Coin_class : public Entity{
private:
    float x_, y_;
    int counter;
public:
    bool collected_;
    Coin_class(float x, float y, sf::Texture &tex);
    void collected(Player_class &player, sf::Sound &coin);
};

#endif // COIN_CLASS_H
