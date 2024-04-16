#include <cmath>
#include <cfloat>
#include <iostream>

#include "physics_world.hpp"

PhysicsWorld::PhysicsWorld(double windowWidth, double windowHeight, int stepsPerFrame, double deltaTimeDivisor) {
	setupBounds(windowWidth, windowHeight);
	gravity = 9.81;
	this->stepsPerFrame = stepsPerFrame;
	this->deltaTimeDivisor = deltaTimeDivisor;
}

void PhysicsWorld::update(double deltaTime) {
	deltaTime /= deltaTimeDivisor;
	for (int step = 0; step < stepsPerFrame; step++)  {
		for (int i = 0; i < objs.size(); i++) {
			objs[i]->updatePosition(deltaTime, gravity);
			objs[i]->resetForceImpulse();
		}
		detectCollisions();
		for (int i = collisions.size()-1; i >= 0; i--) {
			collisions.back().resolve();
			collisions.pop_back();
		}
	}
}

void PhysicsWorld::detectCollisions() {
	for (int i = 0; i < objs.size(); i++) {
		for (int j = i+1; j < objs.size(); j++) {
			Collision collision  = Collision(objs[i], objs[j]);
			if (collision.collides) collisions.push_back(Collision(objs[i], objs[j]));
		}
	}
}

void PhysicsWorld::drawObjects(sf::RenderWindow& window) {
	for (int i = 0; i < objs.size(); i++) {
		if (objs[i]->visible) objs[i]->draw(window);
	}
}

void PhysicsWorld::addObject(CollisionObject* obj) {
	objs.push_back(obj);
}

void PhysicsWorld::setupBounds(double windowWidth, double windowHeight) {
	double thickness = 1000.0;

	leftWall = Rectangle(-thickness / 2.0, windowHeight/ 2.0, DBL_MAX, thickness, windowHeight);
	leftWall.useGravity = false;
	leftWall.isStatic = true;
	leftWall.visible = false;

	rightWall = Rectangle(windowWidth + thickness / 2.0, windowHeight / 2.0, DBL_MAX, thickness, windowHeight);
	rightWall.useGravity = false;
	rightWall.isStatic = true;
	rightWall.visible = false;

	topWall = Rectangle(windowWidth / 2.0, -thickness / 2.0, DBL_MAX, windowWidth, thickness);
	topWall.useGravity = false;
	topWall.isStatic = true;
	topWall.visible = false;

	botWall = Rectangle(windowWidth / 2.0, windowHeight + thickness / 2.0, DBL_MAX, windowWidth, thickness);
	botWall.useGravity = false;
	botWall.isStatic = true;
	botWall.visible = false;

	leftWall.restitution = 0.25;
	rightWall.restitution = 0.25;
	topWall.restitution = 0.25;
	botWall.restitution = 0.25;

	addObject(&leftWall);
	addObject(&rightWall);
	addObject(&topWall);
	addObject(&botWall);
}

void PhysicsWorld::explodeRect(CollisionObject* rectangle, int n, int m) {
	if (!rectangle->explodable) {
		return;
	}

	for (int i = 0; i < objs.size(); i++) {
		if (objs[i]->shape == CollisionShape::Rectangle && objs[i] == rectangle) {
			objs.erase(objs.begin()+i);	

			Rectangle* theRect = (Rectangle*)rectangle;
			double pieceWidth = theRect->width / n;
			double pieceHeight = theRect->height / m;

			for (int j = 0; j < n; j++) {
				for (int k = 0; k < m; k++) {
					double x_pos = j * pieceWidth + (pieceWidth / 2.0) - theRect->width/2.0 + theRect->position.x;
					double y_pos = k * pieceHeight + (pieceHeight / 2.0) - theRect->height/2.0 + theRect->position.y;

					Rectangle* rect = new Rectangle(x_pos, y_pos, theRect->mass / (n * m), pieceWidth, pieceHeight);

					Vec2 newVelocity = Vec2(rect->position - theRect->position);
					double dist = len(newVelocity);
					newVelocity.normalize();
					newVelocity *= 10.0 * sqrt(dist) * rect->mass;
					rect->addImpulse(newVelocity);
					rect->useGravity = true;
					rect->color = theRect->color;
					rect->restitution = 0.1;
					rect->explodable = false;
					
					objs.push_back(rect);
				}
			}

			break;
		}
	}
}

CollisionObject* PhysicsWorld::selectObject(double x, double y) {
	for (int i = 0; i < objs.size(); i++) {
		if (objs[i]->isStatic) continue;
		if (objs[i]->shape == CollisionShape::Rectangle) {
			Rectangle* rect = (Rectangle*)objs[i];

			double x_min = rect->position.x - rect->width / 2.0;
			double x_max = rect->position.x + rect->width / 2.0;
			double y_min = rect->position.y - rect->height / 2.0;
			double y_max = rect->position.y + rect->height / 2.0;

			if (x > x_min && x < x_max && y > y_min && y < y_max){
				return objs[i];
			}	
		}
	}
	return nullptr;
}
