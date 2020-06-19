#include <fstream>
#include <SFML/Graphics.hpp>
#include "map_class.h"
#include "coin_class.h"

extern std::vector<Platform_class> level;
extern std::vector<Coin_class> coins;


void Map_class::draw_map(){

    platforms_tex.loadFromFile("assets/Images/blocks_textures.png");
    coin_tex.loadFromFile("assets/Images/coin.png");

    std::string line;
    std::ifstream file("assets/Maps/level_array.txt");

    if(file.is_open()){
        while(std::getline(file,line)){
           std::vector<int> row;

            for(auto& a : line){
                if(a != ' '){
                    int ia = a - '0';
                    row.emplace_back(ia);
                }
            }
            level_array.emplace_back(row);
        }
        for(unsigned int i = 0; i < level_array.size(); i++){
            for(unsigned int j = 0; j < level_array[i].size(); j++){
                if(level_array[i][j] == 1){
                     Platform_class plats(j * 50, i * 50, 51, 0, platforms_tex);
                     level.emplace_back(plats);
                }
                if(level_array[i][j] == 2){
                     Platform_class plats(j * 50,i * 50, 0, 0, platforms_tex);
                     level.emplace_back(plats);
                }
                if(level_array[i][j] == 4){
                     Platform_class plats(j * 50,i * 50, 152, 0, platforms_tex);
                     level.emplace_back(plats);
                }
                if(level_array[i][j] == 7){
                     Coin_class coin(j * 50, i * 50, coin_tex);
                     coins.emplace_back(coin);
                }
            }
        }
    }
}
