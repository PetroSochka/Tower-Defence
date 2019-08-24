#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include "enemy.hpp"
#pragma once

struct Bullet
{
    sf::CircleShape bul;
    float speed;
};

struct Enemy_info
{
    sf::Vector2f pos_enemy;
    int id_enemy;
    Bullet bullet;
};

class Tower
{
    private:
        unsigned char level;
        sf::Sprite tower;
        float radius;
        float damage;
        std::vector<Enemy_info> fire;

    public:
        Tower();
        void setPosition(sf::Vector2f pos);
        void draw(sf::RenderWindow &window);
        sf::Vector2f getPostion();
        float radius_lenth();
        void push_bullet(int id, sf::Vector2f pos_enemy, sf::Vector2f start);
        void draw_bullet(sf::RenderWindow &window);
        void move_bullet(sf::Vector2f pos_enemy, int id, float time, int &health_enemy);
        void erease_bullet(int index);
        void update_tower();
};