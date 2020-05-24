#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SFML/Graphics.hpp>
#include <hitbox.h>

class Entity : public sf::Sprite{
public:
    sf::Vector2f velocity;
    sf::Vector2f size;
    Hitbox hitbox;
};

#endif // ENTITY_H
