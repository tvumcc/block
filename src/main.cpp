#include <SFML/Graphics.hpp>

#include "physics_world.hpp"
#include "rectangle.hpp"

#define BG_COLOR sf::Color(40, 40, 40)

int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1900u, 1000u), "Blocks", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(0, 0));

	window.setFramerateLimit(144);
	
	double winWidth = window.getSize().x;
	double winHeight = window.getSize().y;
	sf::View view = sf::View(sf::FloatRect(0.0f, 0.0f, window.getSize().x, window.getSize().y));
	window.setView(view);

	PhysicsWorld ctx = PhysicsWorld(window.getSize().x, window.getSize().y, 100, 10000.0);

	Rectangle obj = Rectangle(500.0, 600.0, 10.0, 100.0, 100.0);
	obj.color = sf::Color(0, 255, 0);
	obj.velocity.x = 20.0;

	Rectangle obj2 = Rectangle(1500.0, 600.0, 10.0, 100.0, 200.0);
	obj2.velocity.x = -10.0;

	ctx.addObject(&obj);
	ctx.addObject(&obj2);

	sf::Clock clock;

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
				window.close();
			} else if (event.type == sf::Event::Resized) {
				window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
			} else if (event.type == sf::Event::KeyPressed && (event.key.scancode == sf::Keyboard::Scan::H)) {
				ctx.explodeRect(&obj, 10, 10);
			}
        }

		sf::Time dt = clock.restart();
		window.clear(BG_COLOR);

		ctx.update(dt.asMilliseconds());

		ctx.drawObjects(window);
        window.display();
    }
}
