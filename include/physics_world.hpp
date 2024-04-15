#pragma once
#include <vector>

#include "collision_object.hpp"
#include "rectangle.hpp"

class PhysicsWorld {
public:
	std::vector<Collision> collisions;
	std::vector<CollisionObject*> objs;
	const double gravity = 9.81;
	
	PhysicsWorld();
	void updateObjects(double deltaTime);
	void detectCollisions();
	void drawObjects(sf::RenderWindow& window);
	void addObject(CollisionObject* obj);
	void explodeRect(CollisionObject* rectangle, int n, int m);
};
