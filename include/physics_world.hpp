#pragma once
#include <vector>

#include "rectangle.hpp"

class PhysicsWorld {
public:
	std::vector<Collision> collisions;
	std::vector<Rectangle> objs;
	const double gravity = 9.81;
	
	PhysicsWorld();
	void updateObjects(double deltaTime);
	void detectCollisions();
	void drawObjects(sf::RenderWindow& window);
	void addObject(Rectangle obj);
};
