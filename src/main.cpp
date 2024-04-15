#include <SFML/Graphics.hpp>
#include <iostream>
#include <float.h>

#include "physics_world.hpp"
#include "rectangle.hpp"

#define BG_COLOR sf::Color::Black

int main() {
	sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(1920u, 1080u), "Blocks");
    window.setFramerateLimit(144);

	double winWidth = window.getSize().x;
	double winHeight = window.getSize().y;
	std::cout << "Window Width: " << winWidth << ", Window Height: " << winHeight << std::endl;

	sf::View view = sf::View(sf::FloatRect(0.0f, 0.0f, 1920.0f, 1080.0f));
	window.setView(view);

	Rectangle obj = Rectangle(500.0, 600.0, 10.0, 100.0, 100.0);
	obj.color = sf::Color(0, 255, 0);
	obj.useGravity = true;
	obj.velocity.x = 20.0;
	obj.restitution = 0.95;

	Rectangle obj2 = Rectangle(1500.0, 600.0, 10.0, 100.0, 200.0);
	obj2.useGravity = true;
	obj2.velocity.x = -10.0;
	obj2.restitution = 0.95;

	Rectangle leftWall = Rectangle(-50.0, winHeight / 2.0, DBL_MAX, 100.0, winHeight);
	leftWall.useGravity = false;
	Rectangle rightWall = Rectangle(winWidth + 50.0, winHeight / 2.0, DBL_MAX, 100.0, winHeight);
	rightWall.useGravity = false;
	Rectangle topWall = Rectangle(winWidth / 2.0, -51.0, DBL_MAX, winWidth, 100.0);
	topWall.useGravity = false;
	Rectangle botWall = Rectangle(winWidth / 2.0, winHeight + 51.0, DBL_MAX, winWidth, 100.0);
	botWall.useGravity = false;

	leftWall.restitution = 0.95;
	rightWall.restitution = 0.95;
	topWall.restitution = 0.95;
	botWall.restitution = 0.95;
	leftWall.isStatic = true;
	rightWall.isStatic = true;
	topWall.isStatic = true;
	botWall.isStatic = true;


	PhysicsWorld ctx = PhysicsWorld();
	ctx.addObject(&obj);
	ctx.addObject(&obj2);
	ctx.addObject(&leftWall);
	ctx.addObject(&rightWall);
	ctx.addObject(&topWall);
	ctx.addObject(&botWall);

	sf::Clock clock;

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {

				window.close();
			} else if (event.type == sf::Event::Resized)  {
				window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
			} else if (event.type == sf::Event::KeyPressed) {
				if (event.key.scancode == sf::Keyboard::Scan::H)
					ctx.explodeRect(&obj, 10, 10);
			}
        }

		sf::Time dt = clock.restart();
		window.clear(BG_COLOR);

		for (int i = 0; i < 100; i++) ctx.updateObjects(dt.asMilliseconds() / 10000.0);

		ctx.drawObjects(window);
        window.display();
    }
}
