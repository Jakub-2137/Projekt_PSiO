#include <SFML/Graphics.hpp>
#include "entity.h"
#include "platform_class.h"


Platform_class::Platform_class(float x_, float y_, float w_, float h_, sf::Texture &tex){

    size.x = w_;
    size.y = h_;

    hitbox.left = x_ + 0.f;
    hitbox.right = x_ + size.x - 0.f;
    hitbox.top = y_ + 0.f;
    hitbox.bottom = y_ + size.y - 0.f;

    setTexture(tex);
    setTextureRect(sf::IntRect(51,0,48,48));
    setPosition(x_, y_);
}
