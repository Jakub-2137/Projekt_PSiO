#include "platform_class.h"


Platform_class::Platform_class(float x_, float y_, int cord_x, int cord_y, sf::Texture &tex){

    size.x = 48;
    size.y = 48;

    hitbox.left = x_ + 0.f;
    hitbox.right = x_ + size.x - 0.f;
    hitbox.top = y_ + 0.f;
    hitbox.bottom = y_ + size.y - 0.f;

    setTexture(tex);
    setTextureRect(sf::IntRect(cord_x, cord_y, 48, 48));
    setPosition(x_, y_);
}
