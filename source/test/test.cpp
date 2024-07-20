#include <sfml/Graphics.hpp>

int main()
{
        auto window = sf::RenderWindow{ sf::VideoMode({500, 500}), "Hello World" };
        window.setFramerateLimit(144);

        sf::Font font = sf::Font();
        font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

        auto text = sf::Text();
        text.setFont(font);
        text.setString(L"привет");

        while (window.isOpen()){
            sf::Event event;
            while (window.pollEvent(event)){
                switch(event.type){
                    case sf::Event::Closed:
                        window.close();
                        break;
                }
            }
            window.clear();
            window.draw(text);
            window.display();
        }
}