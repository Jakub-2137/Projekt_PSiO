#include "coin_class.h"

Coin_class::Coin_class(float x, float y, sf::Texture &tex){

    counter = 1;

    collected_ = false;

    x_ = x;
    y_ = y;

    size.x = 100.f;
    size.y = 100.f;

    setTexture(tex);
    setScale(sf::Vector2f(2.25f, 2.25f));
    setPosition(x, y);
}

void Coin_class::collected(Player_class &player, sf::Sound &coin){
    if ((player.getPosition().x < x_ ) &&
        (player.getPosition().x + player.size.x > x_ + size.x) &&
        (player.getPosition().y < y_ + size.y) &&
        (player.getPosition().y + player.size.y > y_)){

        collected_ = true;
        counter--;
    }
    if(counter == 0)
        coin.play();
}
