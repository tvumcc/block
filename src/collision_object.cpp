#include <iostream>
#include <float.h>

#include "collision_object.hpp"
#include "rectangle.hpp"

CollisionObject::CollisionObject() 
	: impulse(Vec2()), force(Vec2()), acceleration(Vec2()), velocity(Vec2()), position(Vec2()), color(sf::Color(255, 0, 0))
{
	mass = 1.0;
	restitution = 1.0;
	useGravity = true;
	isStatic = false;
	shape = CollisionShape::None;
}

CollisionObject::CollisionObject(double x, double y, double mass) {
	this->mass = mass;
	position = Vec2(x, y);
}

void CollisionObject::updatePosition(double deltaTime) {
	acceleration = force / mass;
	velocity += acceleration * deltaTime + impulse / mass;	
	position += velocity * deltaTime;
}

void CollisionObject::addForce(Vec2 v) {
	force += v;
}

void CollisionObject::addImpulse(Vec2 v) {
	impulse += v;
}

void CollisionObject::resetForceImpulse() {
	force = Vec2();
	impulse = Vec2();
}

Collision::Collision(CollisionObject* a, CollisionObject* b) {
	this->a = a;
	this->b = b;

	computeCollision();
}

void Collision::computeCollision() {
	if (a->shape == CollisionShape::Rectangle && b->shape == CollisionShape::Rectangle) {
		Rectangle_vs_Rectangle();
	}
}

void Collision::Rectangle_vs_Rectangle() {
	Rectangle* rect_a = (Rectangle*)a;
	Rectangle* rect_b = (Rectangle*)b;

	double a_min_x = rect_a->position.x - (rect_a->width / 2.0);
	double a_max_x = rect_a->position.x + (rect_a->width / 2.0);
	double a_min_y = rect_a->position.y - (rect_a->height / 2.0);
	double a_max_y = rect_a->position.y + (rect_a->height / 2.0);

	double b_min_x = rect_b->position.x - (rect_b->width / 2.0);
	double b_max_x = rect_b->position.x + (rect_b->width / 2.0);
	double b_min_y = rect_b->position.y - (rect_b->height / 2.0);
	double b_max_y = rect_b->position.y + (rect_b->height / 2.0);

	collides = (a_min_x < b_max_x) && (a_max_x > b_min_x) && (a_min_y < b_max_y) && (a_max_y > b_min_y);

	if (collides) {

		if (abs(a_min_x - b_max_x) - abs(a_max_x - b_min_x) > 0.1) {
			normal.x = b_min_x - a_max_x;
		} else normal.x = a_min_x - b_max_x;

		if (abs(a_min_y - b_max_y) - abs(a_max_y - b_min_y) > 0.1) {
			normal.y = b_min_y - a_max_y;		
		} else normal.y = a_min_y - b_max_y;

		if (abs(normal.y) - abs(normal.x) < 0.1) {
			normal.x = 0.0;
		} else {
			normal.y = 0.0;
		}


		depth = len(normal);
		normal.normalize();
		Vec2 posVector = b->position - a->position;
		if (posVector * normal < 0.0) {
			normal = -1.0 * normal;
		}
	}

}

void Collision::resolve() {
	if (collides) {
		if (a->isStatic && b->isStatic) return;
		else if (a->isStatic) b->position += normal * depth;
		else if (b->isStatic) a->position -= normal * depth;
		else {
			a->position -= normal * depth;
			b->position += normal * depth;
		}


		double e = (a->restitution + b->restitution) / 2.0;

		double numerator = (-(1.0 + e) * (a->velocity - b->velocity)) * normal;
		double denominator = 1.0 / a->mass + 1.0 / b->mass;

		double j = numerator / denominator;
		if (!a->isStatic) a->addImpulse(j * normal);
		if (!b->isStatic) b->addImpulse(-j * normal);
	}
}
