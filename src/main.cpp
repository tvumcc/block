#include <SFML/Graphics.hpp>
#include <iostream>

#define BG_COLOR sf::Color::Black

int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920u, 1080u), "Blocks");
    window.setFramerateLimit(144);

	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2<float>(100,100));
	rect.setFillColor(sf::Color::Green);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(2.0f);
	rect.setPosition(sf::Vector2<float>(100,100));

	bool clicked = false;
	float lastX = sf::Mouse::getPosition(window).x;
	float lastY = sf::Mouse::getPosition(window).y;
	float dx;
	float dy;


    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
				clicked = rect.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window));
			} else if (event.type == sf::Event::MouseButtonReleased) {
				clicked = false;
			} else if (event.type == sf::Event::MouseMoved) {
			}
        }
        window.clear(BG_COLOR);

		dx = sf::Mouse::getPosition(window).x - lastX;
		dy = sf::Mouse::getPosition(window).y - lastY;
		lastX = sf::Mouse::getPosition(window).x;
		lastY = sf::Mouse::getPosition(window).y;

		if (clicked) {
			rect.setPosition(rect.getPosition() + sf::Vector2f(dx, dy));
		}

		window.draw(rect);	

        window.display();
    }
}
