#include "map.hpp"
#include "enemy.hpp"
#include "tower.hpp"
#include "texture.hpp"

const int SizeMap = 20;
extern texture_object object;

map::map()
{
    Map = new node[SizeMap * SizeMap];
    shape = new sf::RectangleShape[SizeMap * SizeMap];
}

map::~map()
{
    if(Map != nullptr)
    {
        delete[] Map;
    }
    if(shape != nullptr)
    {
        delete[] shape;
    }
}

void map::loadFile(std::string path)
{
    std::ifstream in (path, std::ios::binary | std::ios::in);
    if(in.is_open())
    {
        for(int i = 0; i < SizeMap * SizeMap ; i++)
        {
            in.read(reinterpret_cast<char*>(&Map[i].type), sizeof(int));
        }
    }
    in.close();
}

void map::load_texture()
{
    for(int i = 0; i < SizeMap * SizeMap; i++)
    {
        if(Map[i].type == 0)
        {
            Map[i].texture = object.get_texture("blocked");
        }
            if(Map[i].type == 1)
        {
                Map[i].texture = object.get_texture("grass");
        }
        if(Map[i].type == 2)
        {
            Map[i].texture = object.get_texture("stone");
            Map[i].build = true;
        }
    }
}

void map::clear()
{
    if(shape != nullptr)
    {
        delete[]  shape;
        shape = new sf::RectangleShape [SizeMap * SizeMap];
    }
    
    if(Map != nullptr)
    {
       delete[]  Map;
       Map = new node [SizeMap * SizeMap];
    }
    search_way.clear();
}

void map::search()
{  
    int wall = -1;
    int j{0}, k{0};
    int blank = -2;
    int len;
    sf::Vector2f pxy[SizeMap * SizeMap];
    int pos_start_x, pos_start_y, pos_end_x, pos_end_y;
    int grid[SizeMap][SizeMap];
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};
    int d, x, y, l;
    bool stop;
    for(int i = 0; i < SizeMap * SizeMap; i++)
    {
        
        if(Map[i].type == 0 || Map[i].type == 2)
        {
            grid[j][k] = wall;
        }
        if(Map[i].type == 1 || Map[i].type == 3 || Map[i].type == 4)
        {
            grid[j][k] = blank;
        }
        if(Map[i].type == 3)
        {
            pos_start_x = k;
            pos_start_y = j;
        }
        if(Map[i].type == 4)
        {
            pos_end_x = k;
            pos_end_y = j;
        }
        k++;
        if(k == 20)
        {
            k = 0;
            j++;
        }
    }
    d = 0;
    grid[pos_start_y][pos_start_x] = 0;
    do
    {
        stop = true;
        for( y = 0; y < SizeMap; y++)
                
            for( x = 0; x < SizeMap; x++)
                if(grid[y][x] == d)
                {
                    for(l = 0; l < 4; l++)
                    {
                        int iy = y + dy[l], ix = x + dx[l];
                        if(iy >= 0 && iy < SizeMap && ix >= 0 && ix < SizeMap && grid[iy][ix] == blank)
                        {
                            stop = false;
                            grid[iy][ix] = d + 1;
                        }
                    }
                } 
        d++;
    }while( !stop && grid[pos_end_y][pos_end_x] == blank);
    len = grid[pos_end_y][pos_end_x];
    x = pos_end_x;
    y = pos_end_y;
    d = len;
    while(d > 0)
    {
        pxy[d].x = x;
        pxy[d].y = y;
        d--;
        for(l = 0; l < 4; l++)
        {
            int iy = y + dy[l], ix = x + dx[l];
            if(iy >= 0 && iy < SizeMap && ix >= 0 && ix < SizeMap && grid[iy][ix] == d)
            {
                x = x + dx[l];
                y = y + dy[l];
            }
        }
    }
    pxy[0].x = pos_start_x;
    pxy[0].y = pos_start_y;
    for(int i = 0; i < len; i++)
    {
        search_way.push_back(pxy[i] * 32.f);
    }
}

void map::draw(int amount_enemy , int &what_draw, sf::RenderWindow &window)
{
    int game_valute{100}, amout_life{100}, counter{0};
    bool canBuild{false}, fire{false}, canUpdate{false};
    sf::Clock clock, clock_1, clocl_2;
    sf::Sprite temp_1, valute, life;
    sf::Text Update, Valute, Life;
    valute.setTexture(object.get_texture("valute"));
    valute.setPosition({650.0f, 145.0f});
    life.setTexture(object.get_texture("life"));
    life.setPosition({650.0f, 80.0f});
    sf::Font font_update;
    font_update = object.get_font("log");
    Life.setCharacterSize(30);
    Life.setString(std::to_string(amout_life));
    Life.setFont(font_update);
    Life.setPosition({724.0f, 85.0f});
    Life.setFillColor(sf::Color::Red);
    Valute.setCharacterSize(30);
    Valute.setString(std::to_string(game_valute));
    Valute.setFont(font_update);
    Valute.setPosition({724.0f, 155.0f});
    Valute.setFillColor(sf::Color::Yellow);
    Update.setCharacterSize(25);
    Update.setString("Update");
    Update.setFillColor(sf::Color::Black);
    Update.setFont(font_update);
    Update.setPosition({697.0f, 10.0f});
    sf::RectangleShape update;
    update.setFillColor(sf::Color::White);
    update.setSize({100.0f, 40.0f});
    update.setPosition({692, 5});
    int j{0}, k{0};
    window.clear({0, 25, 0});
    int efect{1};
    window.setFramerateLimit(60);
    temp_1.setTexture(object.get_texture("tower"));
    temp_1.setPosition({650, 5});
    sf::Vector2u resize, retreat{ 5, 5 };
    sf::Vector2f size { 32.0f, 32.0f };
    for(int i = 0; i < search_way.size(); i++)
    {
        search_way[i].x += retreat.x;
        search_way[i].y += retreat.y;
    }
    
    Enemy en(search_way);
    Tower tow;
    std::vector<Tower> tower;
    std::vector<Enemy> enemy;
    
    for(int i = 0; i < SizeMap * SizeMap; i++)
    {   
        if(Map[i].type == 3)
        {
            shape[i].setFillColor(sf::Color::Blue);
        }
        if(Map[i].type == 4)
        {
            shape[i].setFillColor(sf::Color::Red);
        }
        if(Map[i].type == 0 || Map[i].type == 1 || Map[i].type == 2) 
        {
            shape[i].setTexture(&Map[i].texture);
        }
        shape[i].setPosition({32.f * j + retreat.x, 32.f * k + retreat.y});
        shape[i].setSize(size);
        
        j++;
        if(j == 20)
        {
            j = 0;
            k++;
        }
    }
    k = 0; 
    j = 0;
    while (window.isOpen())
    {
        double time = clock.getElapsedTime().asMicroseconds();
        double time_1 = clock_1.getElapsedTime().asSeconds();
        double time_2 = clocl_2.getElapsedTime().asSeconds();
        clock.restart();
        time = time/800;
        for(int i = 0; i < SizeMap * SizeMap; i++)
        {
            window.draw(shape[i]);
            
        }
        if(counter <= amount_enemy)
        {
            if(time_1 >= 1.5f)
            {
                clock_1.restart();
                enemy.push_back(en);
                counter++;
            }
        }
        sf::Event event;
        if(sf::IntRect(temp_1.getPosition().x, temp_1.getPosition().y, 32, 32).contains(sf::Mouse::getPosition(window)) &&  sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            canBuild = true;  
        }
        if(canBuild)
        {
            for (int i = 0; i < SizeMap * SizeMap; i++)
            {
                if(Map[i].type == 2 && Map[i].build == true)
                {
                    if(sf::IntRect(shape[i].getPosition().x, shape[i].getPosition().y, 32, 32).contains(sf::Mouse::getPosition(window)) &&  sf::Mouse::isButtonPressed(sf::Mouse::Left) && game_valute >= 30)
                    {
                        tow.setPosition(shape[i].getPosition());
                        tower.push_back(tow);
                        game_valute -= 30;
                        canBuild = false;
                        Map[i].build = false;
                    }
                }
            }
        }
        for (int i = 0; i < tower.size(); i++)
        {
            tower[i].draw(window);
        }
        for (int i = 0; i < tower.size(); i++)
        {
            for (int j = 0; j < enemy.size(); j++)
            {
                if(sqrt(pow((tower[i].getPostion().x - enemy[j].getPosition().x), 2) + pow((tower[i].getPostion().y - enemy[j].getPosition().y), 2)) <= tower[i].radius_lenth())
                {
                    if(time_2 >= 1.0f)
                    {
                        tower[i].push_bullet(j, enemy[j].getPosition(), tower[i].getPostion());
                        clocl_2.restart();
                        break;
                    }
                }
            }
            
        }
        for(int i = 0; i < enemy.size(); i++)
        {
            enemy[i].move(search_way, time/2);
            enemy[i].draw(window);
            if(enemy[i].health <= 0)
            {
                game_valute += 10;
                enemy.erase(enemy.begin() + i);
                
            }
            if(enemy[i].getPosition().x == search_way[search_way.size()-1].x && enemy[i].getPosition().y == search_way[search_way.size()-1].y - 10)
            {
                enemy.erase(enemy.begin() + i);
                amout_life -= 25;
            }   
        }
        for (int i = 0; i < tower.size(); i++)
        {
            for (int j = 0; j < enemy.size(); j++)
            {
                tower[i].move_bullet(enemy[j].getPosition(), j, time, enemy[j].health);
                tower[i].draw_bullet(window);
            }
        }
        
        
        if(sf::IntRect(update.getPosition().x, update.getPosition().y, 100, 50).contains(sf::Mouse::getPosition(window)))
        {
            update.setOutlineThickness(3.0f);
            update.setOutlineColor(sf::Color::Yellow);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && game_valute >= 40 && tower.size() > 0)
            {
                canUpdate = true;
                Update.setFillColor(sf::Color::Red);
            }
        }
        else
        {
            update.setOutlineColor({0, 25, 0});
        }
        if(canUpdate)
        {
            for(int i = 0; i < tower.size(); i++)
            {
                if(sf::IntRect(tower[i].getPostion().x, tower[i].getPostion().y, 32, 32).contains(sf::Mouse::getPosition(window)) &&  sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    tower[i].update_tower();
                    canUpdate = false;
                    game_valute -= 40;
                    Update.setFillColor(sf::Color::Black);
                }
            }
        }
        if(tower.size() == 0)
        {
            canUpdate = false;
        }
        Valute.setString(std::to_string(game_valute));
        Life.setString(std::to_string(amout_life));
        window.draw(Valute);
        window.draw(life);
        window.draw(Life);
        window.draw(temp_1);
        window.draw(update);
        window.draw(valute);
        window.draw(Update);
        window.display();
        window.clear({0, 25, 0});
        if(amout_life <= 0 || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            what_draw = 1;
            break;
        }
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                what_draw = -1;
            }
        }
    }
}

void map::play_exit(sf::RenderWindow &window, int &what_draw)
{
    window.clear(sf::Color::Blue);
    sf::Text Play, Exit;
    sf::Font font = object.get_font("log");
    Play.setCharacterSize(60);
    Play.setFillColor(sf::Color::Cyan);
    Play.setPosition({345.0f, 157.0f});
    Play.setString("Play");
    Play.setFont(font);
    Exit.setCharacterSize(60);
    Exit.setFillColor(sf::Color::Cyan);
    Exit.setPosition({345.0f, 374.0f});
    Exit.setString("Exit");
    Exit.setFont(font);
    while(window.isOpen())
    {
        if(sf::IntRect(Play.getPosition().x + 5, Play.getPosition().y + 15, 165, 50).contains(sf::Mouse::getPosition(window)))
        {
            Play.setFillColor(sf::Color::Green);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                what_draw = 1;
                break;
            }
            
        }
        else
        {
            Play.setFillColor(sf::Color::Cyan);
        }
        if(sf::IntRect(Exit.getPosition().x, Exit.getPosition().y, 165, 65).contains(sf::Mouse::getPosition(window)))
        {
            Exit.setFillColor(sf::Color::Green);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                what_draw = -1;
                break;
            }
            
        }
        else
        {
            Exit.setFillColor(sf::Color::Cyan);
        }
        sf::Event event;
        window.draw(Play);
        window.draw(Exit);
        window.display();
        window.clear(sf::Color::Blue);
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                what_draw = -1;
            }
        }
    }
}

int map::levels(sf::RenderWindow &window, int &what_draw)
{
    window.clear(sf::Color::Blue);
    sf::Text Level_1, Level_2, Level_3, Level_4, Level_5, Back;
    sf::Font font = object.get_font("log");
    Back.setCharacterSize(30);
    Back.setFillColor(sf::Color::Cyan);
    Back.setPosition({340.0f, 57.0f});
    Back.setString("Back");
    Back.setFont(font);
    Level_1.setCharacterSize(30);
    Level_1.setFillColor(sf::Color::Cyan);
    Level_1.setPosition({335.0f, 149.0f});
    Level_1.setString("Level 1");
    Level_1.setFont(font);
    Level_2.setCharacterSize(30);
    Level_2.setFillColor(sf::Color::Cyan);
    Level_2.setPosition({335.0f, 246.0f});
    Level_2.setString("Level 2");
    Level_2.setFont(font);
    Level_3.setCharacterSize(30);
    Level_3.setFillColor(sf::Color::Cyan);
    Level_3.setPosition({335.0f, 338.0f});
    Level_3.setString("Level 3");
    Level_3.setFont(font);
    Level_4.setCharacterSize(30);
    Level_4.setFillColor(sf::Color::Cyan);
    Level_4.setPosition({335.0f, 430.0f});
    Level_4.setString("Level 4");
    Level_4.setFont(font);
    Level_5.setCharacterSize(30);
    Level_5.setFillColor(sf::Color::Cyan);
    Level_5.setPosition({335.0f, 522.0f});
    Level_5.setString("Level 5");
    Level_5.setFont(font);
    while (window.isOpen())
    {
        if(sf::IntRect(Level_1.getPosition().x, Level_1.getPosition().y, 100, 30).contains(sf::Mouse::getPosition(window)))
        {
            Level_1.setFillColor(sf::Color::Green);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                what_draw = 2;
                return 1;
            }
        }
        else
        {
            Level_1.setFillColor(sf::Color::Cyan);
        }
        if(sf::IntRect(Level_2.getPosition().x, Level_2.getPosition().y, 100, 30).contains(sf::Mouse::getPosition(window)))
        {
            Level_2.setFillColor(sf::Color::Green);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                what_draw = 2;
                return 2;
            }
        }
        else
        {
            Level_2.setFillColor(sf::Color::Cyan);
        }
        if(sf::IntRect(Level_3.getPosition().x, Level_3.getPosition().y, 100, 30).contains(sf::Mouse::getPosition(window)))
        {
            Level_3.setFillColor(sf::Color::Green);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                what_draw = 2;
                return 3;
            }
        }
        else
        {
            Level_3.setFillColor(sf::Color::Cyan);
        }
        if(sf::IntRect(Level_4.getPosition().x, Level_4.getPosition().y, 100, 30).contains(sf::Mouse::getPosition(window)))
        {
            Level_4.setFillColor(sf::Color::Green);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                what_draw = 2;
                return 4;
            }
        }
        else
        {
            Level_4.setFillColor(sf::Color::Cyan);
        }
        if(sf::IntRect(Level_5.getPosition().x, Level_5.getPosition().y, 100, 30).contains(sf::Mouse::getPosition(window)))
        {
            Level_5.setFillColor(sf::Color::Green);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                what_draw = 2;
                return 5;
            }
        }
        else
        {
            Level_5.setFillColor(sf::Color::Cyan);
        }
        if(sf::IntRect(Back.getPosition().x, Back.getPosition().y, 80, 30).contains(sf::Mouse::getPosition(window)))
        {
            Back.setFillColor(sf::Color::Green);
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                what_draw = 0;
                break;
            }
        }
        else
        {
            Back.setFillColor(sf::Color::Cyan);
        }   
        sf::Event event;
        window.draw(Level_1);
        window.draw(Level_2);
        window.draw(Level_3);
        window.draw(Level_4);
        window.draw(Level_5);
        window.draw(Back);
        window.display();
        window.clear(sf::Color::Blue);
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                what_draw = -1;
            }
        }
        
    }
    return what_draw;    
}
