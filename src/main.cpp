#include <SFML/Graphics.hpp>
#include <iostream>

#include "physics_world.hpp"

#define BG_COLOR sf::Color::Black

int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920u, 1080u), "Blocks");
    window.setFramerateLimit(144);

	sf::View view = sf::View(sf::FloatRect(0.0f, 0.0f, 1920.0f, 1080.0f));
	window.setView(view);

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

	Rectangle obj = Rectangle(100.0, 100.0);
	obj.position = Vec2(100.0, 200.0);
	obj.red = 255.0; obj.blue = 255.0;
	obj.velocity.x = 20.0;
	obj.mass = 10.0;
	obj.e = 1.0;

	Rectangle obj2 = Rectangle(100.0, 100.0);
	obj2.position = Vec2(800.0, 190.0);
	obj2.red = 10.0; obj.blue = 10.0;
	obj2.velocity.x = -10.0;
	obj2.mass = 10.0;
	obj2.e = 0.95;

	PhysicsWorld ctx = PhysicsWorld();
	ctx.addObject(obj);
	ctx.addObject(obj2);

	sf::Clock clock;

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
				clicked = rect.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window));
			} else if (event.type == sf::Event::MouseButtonReleased) {
				clicked = false;
			} else if (event.type == sf::Event::Resized)  {
				window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
			}
        }

		sf::Time dt = clock.restart();
		window.clear(BG_COLOR);

		dx = sf::Mouse::getPosition(window).x - lastX;
		dy = sf::Mouse::getPosition(window).y - lastY;
		lastX = sf::Mouse::getPosition(window).x;
		lastY = sf::Mouse::getPosition(window).y;

		if (clicked) rect.setPosition(rect.getPosition() + sf::Vector2f(dx, dy));

		for (int i = 0; i < 100; i++) ctx.updateObjects(dt.asMilliseconds() / 10000.0);

		ctx.drawObjects(window);

		window.draw(rect);	

        window.display();
    }
}
