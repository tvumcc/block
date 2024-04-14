#include "physics_world.hpp"
#include <iostream>

PhysicsWorld::PhysicsWorld() {
}

void PhysicsWorld::updateObjects(double deltaTime) {
	for (int i = 0; i < objs.size(); i++) {
		//objs[i].addForce(Vec2(0.0, gravity * objs[i].mass));
		objs[i].updatePosition(deltaTime);
		objs[i].resetForceImpulse();
	}

	detectCollisions();
	for (int i = collisions.size()-1; i >= 0; i--) {
		collisions.back().resolve();
		collisions.pop_back();
	}
}

void PhysicsWorld::detectCollisions() {
	for (int i = 0; i < objs.size(); i++) {
		for (int j = i+1; j < objs.size(); j++) {
			collisions.push_back(Collision(&objs[i], &objs[j]));
		}
	}
}

void PhysicsWorld::drawObjects(sf::RenderWindow& window) {
	for (int i = 0; i < objs.size(); i++) {
		objs[i].draw(window);
	}
}

void PhysicsWorld::addObject(Rectangle obj) {
	objs.push_back(obj);
}
