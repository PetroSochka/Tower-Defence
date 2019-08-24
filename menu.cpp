#include "menu.hpp"
#include "texture.hpp"

extern texture_object object;

menu::menu()
{
    font = object.get_font("log");
    font_pass = object.get_font("pass");
    passw.setTexture(object.get_texture("password"));
    passw.setPosition({215, 170});
    passw.setColor(sf::Color::Cyan);
    log.setTexture(object.get_texture("login"));
    log.setPosition({215, 50});
    log.setColor(sf::Color::Cyan);
    sig.setTexture(object.get_texture("sign_in"));
    sig.setColor(sf::Color::Black);
    sig.setPosition({100, 300});
    sup.setTexture(object.get_texture("sign_up"));
    sup.setPosition({330, 300});
    sup.setColor(sf::Color::Black);
    text_log.setFont(font);
    text_log.setCharacterSize(30);
    text_log.setStyle(sf::Text::Regular);
    text_log.setPosition({160, 100});
    text_log.setFillColor(sf::Color::Black);
    text_pass.setFont(font_pass);
    text_pass.setCharacterSize(30);
    text_pass.setStyle(sf::Text::Regular);
    text_pass.setPosition({160, 220});
    text_pass.setFillColor(sf::Color::Black);
}

bool menu::readFile(menu::user to_read)
{
    std::string buff;
    std::ifstream in(to_read.name, std::ios::in | std::ios::binary);
    if(in.is_open())
    {
        std::getline(in, buff, '\0');
        if (to_read.password == buff)
        {
            in.close();
            return true;
            }
            else
            {
                return false;
            }
        
    }
    else 
    {
        return false;
    }
}

void menu::writeFile(menu::user to_write)
{
    std::ofstream out(to_write.name.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    if(out.is_open())
    {
        out.write(to_write.password.c_str(), to_write.password.size());
    }
    out.close();
}

bool menu::draw()
{
    sf::RenderWindow window(sf::VideoMode(600, 400), "Tower Defence");
    menu::user str;
    sf::RectangleShape activeArrLog, activeArrPass;
    activeArrLog.setSize({300, 40});
    activeArrLog.setFillColor(sf::Color::White);
    activeArrLog.setPosition({150, 100});
    activeArrPass.setSize({300, 40});
    activeArrPass.setFillColor(sf::Color::White);
    activeArrPass.setPosition({150, 220});
    window.clear(sf::Color::Blue);
    window.draw(activeArrLog);
    window.draw(activeArrPass);
    window.draw(passw);
    window.draw(log);
    window.draw(sig);
    window.draw(sup);
    window.display();
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
            if(sf::IntRect(150, 100, 300, 40).contains(sf::Mouse::getPosition(window)) &&  sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                activeArrLog.setOutlineThickness(5.0f);
                activeArrLog.setOutlineColor(sf::Color::Red);
                activeArrPass.setOutlineColor(sf::Color::Blue);
                canWriteLog = true;
                canWritePass = false;
            }
            if(sf::IntRect(150, 220, 300, 40).contains(sf::Mouse::getPosition(window)) &&  sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                activeArrPass.setOutlineThickness(5.0f);
                activeArrPass.setOutlineColor(sf::Color::Red);
                activeArrLog.setOutlineColor(sf::Color::Blue);
                canWriteLog = false;
                canWritePass = true;
            }
            if(canWriteLog)
            {
                if(event.type == sf::Event::TextEntered)
                {
                    
                    str.name += static_cast<char>(event.text.unicode);
                    text_log.setString(str.name);
                    if(str.name.size() > 1)
                    {
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                        {
                            str.name.pop_back();
                            str.name.pop_back();
                            text_log.setString(str.name);
                            window.draw(text_log);
                        }
                    }
                    if(str.name.size() > 19)
                    {
                        window.close();
                        return false;
                    }

                }
            }
            if(canWritePass)
            {
                if(event.type == sf::Event::TextEntered)
                {
                    str.password += static_cast<char>(event.text.unicode);
                    text_pass.setString(str.password);
                    if(str.password.size() > 1)
                    {
                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                        {
                            str.password.pop_back();
                            str.password.pop_back();
                            text_pass.setString(str.password);
                            window.draw(text_pass);
                        }
                    }
                    if(str.password.size() > 19)
                    {
                        window.close();
                        return false;
                    }
                }
            }
            if(sf::IntRect(330, 300, 180, 50).contains(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sup.setColor(sf::Color::Red);
                    window.draw(sup);
                    window.display();
                    if(str.name.size() > 0 && str.password.size() > 0)
                    {
                        writeFile(str);
                        str.name.erase();
                        str.password.erase();
                        text_pass.setString(str.password);
                        text_log.setString(str.name);
                        window.draw(text_log);
                        window.draw(text_pass);
                        window.display();
                    }
                }
            }
            else
            {
                sup.setColor(sf::Color::Black);
            }
            
            if(sf::IntRect(100, 300, 180, 50).contains(sf::Mouse::getPosition(window)))
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    sig.setColor(sf::Color::Red);
                    window.draw(sig);
                    window.display();
                    if(str.name.size() > 0 && str.password.size() > 0)
                    {
                        if(readFile(str))
                        {
                            window.close();
                            return true;
                        }
                        else
                        {
                            str.name.erase();
                            str.password.erase();
                            text_pass.setString(str.password);
                            text_log.setString(str.name);
                            window.draw(text_log);
                            window.draw(text_pass);
                            window.display();
                        }
                    }
                }
            }
            else
            {
                sig.setColor(sf::Color::Black);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)|| sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                activeArrLog.setOutlineColor(sf::Color::Blue);
                activeArrPass.setOutlineColor(sf::Color::Blue);
                canWriteLog = false;
                canWritePass = false;
            }
            window.draw(log);
            window.draw(activeArrLog);
            window.draw(activeArrPass);
            window.draw(text_log);
            window.draw(text_pass);
            window.draw(passw);
            window.draw(sig);
            window.draw(sup);
            window.display();
            window.clear(sf::Color::Blue);
        }
    }
    return false;
}
