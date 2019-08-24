#include <vector>
#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#pragma once

struct node 
{
    int type;
    sf::Texture texture;
    bool build;
};

class map
{
    private:
        node *Map;
        std::vector<sf::Vector2f>  search_way;
        sf::RectangleShape *shape;
    public:
        void draw(int amount_enemy, int &what_draw, sf::RenderWindow &window);
        void loadFile(std::string path);
        void load_texture();
        void search();
        void play_exit(sf::RenderWindow &window, int &what_draw);
        int levels(sf::RenderWindow &window, int &what_draw);
        void clear();
        map();
       ~map();
};