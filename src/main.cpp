#include "map.hpp"
#include "texture.hpp"
#include "menu.hpp"

texture_object object;

int main()
{
    int what_draw{0}, which_level{0};
    menu Login;
    map Map;
    if(Login.draw())
    {
        sf::RenderWindow window(sf::VideoMode(810, 650), "Tower Defence", sf::Style::Close);
        window.setFramerateLimit(60);
        while(what_draw >= 0)
        {
            if(what_draw == 0)
            {
                Map.play_exit(window, what_draw);
            }
            if(what_draw == 1)
            {
                which_level = Map.levels(window, what_draw);
                if(what_draw == 2 && which_level == 1)
                {
                    Map.loadFile("maps/level1.bin");
                    Map.load_texture();
                    Map.search();
                    Map.draw(10,what_draw, window);
                    Map.clear();
                }
                if(what_draw == 2 && which_level == 2)
                {
                    Map.loadFile("maps/level2.bin");
                    Map.load_texture();
                    Map.search();
                    Map.draw(15, what_draw, window);
                    Map.clear();
                }
                if(what_draw == 2 && which_level == 3)
                {
                    Map.loadFile("maps/level3.bin");
                    Map.load_texture();
                    Map.search();
                    Map.draw(20, what_draw, window);
                    Map.clear();
                }
                if(what_draw == 2 && which_level == 4)
                {
                    Map.loadFile("maps/level4.bin");
                    Map.load_texture();
                    Map.search();
                    Map.draw(25, what_draw, window);
                    Map.clear();
                }
                if(what_draw == 2 && which_level == 5)
                {
                    Map.loadFile("maps/level5.bin");
                    Map.load_texture();
                    Map.search();
                    Map.draw(30, what_draw, window);
                    Map.clear();
                }
            }
        }
    }
    return 0;
}