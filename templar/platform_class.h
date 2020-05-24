#ifndef PLATFORM_CLASS_H
#define PLATFORM_CLASS_H
#pragma once
#include <SFML/Graphics.hpp>
#include <entity.h>


class Platform_class : public Entity{
public:
    Platform_class(float x, float y, float w, float h, sf::Texture &tex);
};

#endif // PLATFORM_CLASS_H
