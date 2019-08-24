#include "texture.hpp"

    void texture_object::load_textures()
    {
        sf::Texture temp;
        temp.loadFromFile("texture/grass.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("grass", temp));
        temp.loadFromFile("texture/stone.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("stone", temp));
        temp.loadFromFile("texture/blocked.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("blocked", temp));
        temp.loadFromFile("texture/enem.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("enemy", temp));
        temp.loadFromFile("texture/login.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("login", temp));
        temp.loadFromFile("texture/password.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("password", temp));
        temp.loadFromFile("texture/sign_in.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("sign_in", temp));
        temp.loadFromFile("texture/sign_up.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("sign_up", temp));
        temp.loadFromFile("texture/tower.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("tower", temp));
        temp.loadFromFile("texture/updated_tower.png"); 
        objects_T.insert(std::pair<std::string, sf::Texture>("updated_tower", temp));
        temp.loadFromFile("texture/valute.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("valute", temp));
        temp.loadFromFile("texture/life.png");
        objects_T.insert(std::pair<std::string, sf::Texture>("life", temp));

    }

    void texture_object::load_font()
    {
        sf::Font temp;
        temp.loadFromFile("font/password.ttf");
        objects_F.insert(std::pair<std::string, sf::Font>("pass", temp));
        temp.loadFromFile("font/16900.ttf");
        objects_F.insert(std::pair<std::string, sf::Font>("log", temp));
    }

    texture_object::texture_object()
    {
        load_font();
        load_textures();
    }

    sf::Font &texture_object::get_font(std::string name_f)
    {
        return objects_F.at(name_f);
    }

    sf::Texture &texture_object::get_texture(std::string name)
    {
        return objects_T.at(name);
    }
