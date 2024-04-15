#include <cmath>
#include <cfloat>

#include "physics_world.hpp"

PhysicsWorld::PhysicsWorld(double windowWidth, double windowHeight, int stepsPerFrame, double deltaTimeDivisor) {
	setupBounds(windowWidth, windowHeight);
	this->stepsPerFrame = stepsPerFrame;
	this->deltaTimeDivisor = deltaTimeDivisor;
}

void PhysicsWorld::update(double deltaTime) {
	deltaTime /= deltaTimeDivisor;
	for (int step = 0; step < stepsPerFrame; step++)  {
		for (int i = 0; i < objs.size(); i++) {
			if (objs[i]->useGravity) objs[i]->addForce(Vec2(0.0, gravity * objs[i]->mass));
			objs[i]->updatePosition(deltaTime);
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
	leftWall = Rectangle(-50.0, windowHeight/ 2.0, DBL_MAX, 100.0, windowHeight);
	leftWall.useGravity = false;
	leftWall.isStatic = true;
	leftWall.visible = false;

	rightWall = Rectangle(windowWidth + 50.0, windowHeight / 2.0, DBL_MAX, 100.0, windowHeight);
	rightWall.useGravity = false;
	rightWall.isStatic = true;
	rightWall.visible = false;

	topWall = Rectangle(windowWidth / 2.0, -51.0, DBL_MAX, windowWidth, 100.0);
	topWall.useGravity = false;
	topWall.isStatic = true;
	topWall.visible = false;

	botWall = Rectangle(windowWidth / 2.0, windowHeight + 51.0, DBL_MAX, windowWidth, 100.0);
	botWall.useGravity = false;
	botWall.isStatic = true;
	botWall.visible = false;

	addObject(&leftWall);
	addObject(&rightWall);
	addObject(&topWall);
	addObject(&botWall);
}

void PhysicsWorld::explodeRect(CollisionObject* rectangle, int n, int m) {
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
					newVelocity *= 2.0 * sqrt(dist);
					rect->addImpulse(newVelocity);
					rect->useGravity = true;
					rect->color = theRect->color;
					rect->restitution = 0.4;
					
					objs.push_back(rect);
				}
			}

			break;
		}
	}
}
