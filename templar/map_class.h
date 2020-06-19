#ifndef MAP_CLASS_H
#define MAP_CLASS_H
#pragma once
#include <vector>
#include "platform_class.h"

class Map_class{
private:
    std::vector<std::vector<int>> level_array;    
    sf::Texture platforms_tex, coin_tex;
public:
    void draw_map();
};

#endif // MAP_CLASS_H


