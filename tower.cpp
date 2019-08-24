#include "tower.hpp"
#include "texture.hpp"

extern texture_object object;
 
Tower::Tower()
{
    level = 1;
    radius = 128;
    damage = 30;
    tower.setTexture(object.get_texture("tower"));
}

void Tower::draw(sf::RenderWindow &window)
{
    window.draw(tower);
}

void Tower::setPosition(sf::Vector2f pos)
{
    tower.setPosition(pos);
}

sf::Vector2f Tower::getPostion()
{

    return tower.getPosition();
}

float Tower::radius_lenth()
{
    return radius;
}

void Tower::push_bullet(int id, sf::Vector2f pos_enemy, sf::Vector2f start)
{
    Enemy_info temp;
    if(level == 1)
    {
        temp.bullet.bul.setPosition(start);
        temp.bullet.bul.setFillColor(sf::Color::Red);
        temp.bullet.bul.setRadius(5.0f);
        temp.bullet.speed = 2;
        temp.id_enemy = id;
        temp.pos_enemy = pos_enemy;
    }
    if(level == 2)
    {
        temp.bullet.bul.setPosition(start);
        temp.bullet.bul.setFillColor(sf::Color::Cyan);
        temp.bullet.bul.setRadius(7.0f);
        temp.bullet.speed = 2;
        temp.id_enemy = id;
        temp.pos_enemy = pos_enemy;
    }
    fire.push_back(temp);
}

void  Tower::draw_bullet(sf::RenderWindow &window)
{
    for (int i = 0; i < fire.size(); i++)
    {
        window.draw(fire[i].bullet.bul);
    }
}

void Tower::move_bullet(sf::Vector2f pos_enemy, int id, float time, int &health_enemy )
{
    float distance{0.0f};
    sf::Vector2f temp;
    for (int i = 0; i < fire.size(); i++)
    {
        if(fire[i].id_enemy == id)
        {
            fire[i].pos_enemy = pos_enemy;
            distance = sqrt(pow(((fire[i].pos_enemy.x  + 16) - fire[i].bullet.bul.getPosition().x), 2) + pow(((fire[i].pos_enemy.y + 16) - fire[i].bullet.bul.getPosition().y), 2));
            if(distance > 4)
            {
                temp = fire[i].bullet.bul.getPosition();
                temp.x += 0.1 * time * 3 * ((fire[i].pos_enemy.x + 16) - temp.x) / distance;
                temp.y += 0.1 * time * 3 * ((fire[i].pos_enemy.y + 16) - temp.y) / distance;
                fire[i].bullet.bul.setPosition(temp);
            }
            else if (distance <= 4)
            {
                fire.erase(fire.begin() + i);
                health_enemy -= damage;
            }
        }
        else if (sqrt(pow(((fire[i].pos_enemy.x) - fire[i].bullet.bul.getPosition().x), 2) + pow(((fire[i].pos_enemy.y) - fire[i].bullet.bul.getPosition().y), 2)) >= radius)
        {
            fire.erase(fire.begin() + i);
        }
    }
}

void  Tower::erease_bullet(int index)
{
    for (int i = 0; i < fire.size(); i++)
    {
        if(fire[i].id_enemy == index)
        {
            fire.erase(fire.begin() + i);
        }
    }
}
void Tower::update_tower()
{
    tower.setTexture(object.get_texture("updated_tower"));
    for(int i = 0; i < fire.size(); i++)
    {
        fire[i].bullet.bul.setFillColor(sf::Color::Cyan);
        fire[i].bullet.bul.setRadius(7.0f);
    }
    radius = 160.0f;
    damage = 45.0f;
    level = 2;
}

