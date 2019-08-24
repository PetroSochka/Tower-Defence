#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#pragma once

class texture_object
{
    private:
        std::unordered_map<std::string, sf::Texture> objects_T;
        std::unordered_map<std::string, sf::Font> objects_F;
    public:
        void load_textures();
        void load_font();
        texture_object();
        sf::Font &get_font(std::string name_f);
        sf::Texture &get_texture(std::string name);
};