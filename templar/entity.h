#ifndef ENTITY_H
#define ENTITY_H
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <hitbox.h>

class Entity : public sf::Sprite{
public:
    sf::Vector2f velocity;
    sf::Vector2f size, frame_size, frames_amount;
    std::vector<sf::IntRect> anim_frames;
    Hitbox hitbox;
};

#endif // ENTITY_H
