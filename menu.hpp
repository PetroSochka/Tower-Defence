#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#pragma once 

class menu
{
    private:
    bool canWriteLog{false}, canWritePass{false}, can_search{false};
    sf::Sprite passw, log, sig, sup;
    sf::Text text_log, text_pass;
    sf::Font font, font_pass;

    public:
    struct user
    {   
        std::string name;
        std::string password;
    };
    
    menu();
    bool draw();
    bool readFile(user to_read);
    void writeFile(user to_write);
};