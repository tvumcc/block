#include <cmath>
#include <iostream>

#include "collision.hpp"
#include "rectangle.hpp"

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

void Collision::resolve() {
	if (collides) {
		if (a->isStatic && b->isStatic) return;
		else if (a->isStatic) b->position += normal * depth;
		else if (b->isStatic) a->position -= normal * depth;
		else {
			double a_percent = 1.0 - (a->mass / (a->mass + b->mass));
			double b_percent = 1.0 - (b->mass / (a->mass + b->mass));

			a->position -= normal * (depth * 0.5);
			b->position += normal * (depth * 0.5);
		}


		double e = std::min(a->restitution, b->restitution);
		double numerator = (-(1.0 + e) * (a->velocity - b->velocity)) * normal;
		double denominator = 1.0 / a->mass + 1.0 / b->mass;

		double j = numerator / denominator;
		if (!a->isStatic) a->addImpulse(j * normal);
		if (!b->isStatic) b->addImpulse(-j * normal);
	}
}

bool lessThanE(double a, double b, double epsilon = 1e-8) {
	return a - b <= epsilon;
}

bool greaterThanE(double a, double b, double epsilon = 1e-8) {
	return a - b >= epsilon;
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

	collides = lessThanE(a_min_x, b_max_x) && greaterThanE(a_max_x, b_min_x) && lessThanE(a_min_y, b_max_y) && greaterThanE(a_max_y, b_min_y);

	if (collides) {
		if (greaterThanE(std::fabs(a_min_x - b_max_x), std::fabs(a_max_x - b_min_x))) normal.x = b_min_x - a_max_x;
		else normal.x = a_min_x - b_max_x;

		if (greaterThanE(std::fabs(a_min_y - b_max_y), std::fabs(a_max_y - b_min_y))) normal.y = b_min_y - a_max_y;
		else normal.y = a_min_y - b_max_y;

		if (lessThanE(std::fabs(normal.y), std::fabs(normal.x))) normal.x = 0.0;
		else normal.y = 0.0;


		depth = len(normal);
		if (depth != 0.0) normal.normalize();

		// Flip normal depending on the orientation of the two objects
		Vec2 posVector = b->position - a->position;
		if (posVector * normal < 0.0) normal = -1.0 * normal;
	}

}
