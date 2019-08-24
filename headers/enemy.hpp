#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

class Enemy
{
private:
    sf::Sprite enemy;
    int count = 0;
    float frame = 0;

public:
    int health;
    void draw(sf::RenderWindow &);
    Enemy(std::vector<sf::Vector2f> search_way);
    void move(std::vector<sf::Vector2f>, float);
    sf::Vector2f getPosition();
};