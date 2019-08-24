#include "enemy.hpp"
#include "texture.hpp"

extern texture_object object;

Enemy::Enemy(std::vector<sf::Vector2f> search_way)
{
    enemy.setTexture(object.get_texture("enemy"));
    enemy.setPosition({search_way[0].x, search_way[0].y - 10});
    enemy.setTextureRect(sf::IntRect(1 * 0, 1 * 20 , 33, 50));
    health = 90;
}

void Enemy::move(std::vector<sf::Vector2f> search_way, float time)
{
    frame += 0.004 * time;
    if(frame > 3)
    {
        frame = 0;
    }
    if(enemy.getPosition().x > search_way[count].x)//left
    {
        enemy.setTextureRect(sf::IntRect(static_cast<int>(frame) * 32, 86 , 32, 42));
        enemy.move({static_cast<float>(time * -0.1), 0});
        if(enemy.getPosition().x < search_way[count].x)
        {
            enemy.setPosition({search_way[count].x, search_way[count].y - 10});
        }
    }
    else if(enemy.getPosition().x < search_way[count].x)//right
    {
        enemy.setTextureRect(sf::IntRect(static_cast<int>(frame) * 32, 150 , 32, 42));
        enemy.move({static_cast<float>(0.1 * time), 0});
        if(enemy.getPosition().x > search_way[count].x)
        {
            enemy.setPosition({search_way[count].x, search_way[count].y - 10});
        }
    }
    else if(enemy.getPosition().y < search_way[count].y - 10)//down
    {
        enemy.setTextureRect(sf::IntRect(static_cast<int>(frame) * 32, 20 , 32, 42));
        enemy.move({0, static_cast<float>(0.1 * time)});
        if(enemy.getPosition().y > search_way[count].y - 10)
        {
            enemy.setPosition({search_way[count].x, search_way[count].y - 10});
        }
    }
    else if(enemy.getPosition().y > search_way[count].y - 10)//up
    {
        enemy.setTextureRect(sf::IntRect(static_cast<int>(frame) * 32, 214 , 32, 42));
        enemy.move({0, static_cast<float>(time * -0.1)});
        if(enemy.getPosition().y < search_way[count].y - 10)
        {
            enemy.setPosition({search_way[count].x, search_way[count].y - 10});
        }
    }
    else 
    {
        count++;
    }
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(enemy);
}

sf::Vector2f Enemy::getPosition()
{
    return enemy.getPosition();
}
