#include <cmath>

#include "physics_world.hpp"

PhysicsWorld::PhysicsWorld() {}

void PhysicsWorld::updateObjects(double deltaTime) {
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

void PhysicsWorld::detectCollisions() {
	for (int i = 0; i < objs.size(); i++) {
		for (int j = i+1; j < objs.size(); j++) {
			collisions.push_back(Collision(objs[i], objs[j]));
		}
	}
}

void PhysicsWorld::drawObjects(sf::RenderWindow& window) {
	for (int i = 0; i < objs.size(); i++) {
		objs[i]->draw(window);
	}
}

void PhysicsWorld::addObject(CollisionObject* obj) {
	objs.push_back(obj);
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
