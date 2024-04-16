#include "collision_object.hpp"

CollisionObject::CollisionObject() 
	: impulse(Vec2()), force(Vec2()), acceleration(Vec2()), velocity(Vec2()), position(Vec2()), color(sf::Color(255, 0, 0))
{
	mass = 1.0;
	restitution = 0.95;
	useGravity = true;
	isStatic = false;
	visible = true;
	explodable = true;
	shape = CollisionShape::None;
}

CollisionObject::CollisionObject(double x, double y, double mass) {
	this->mass = mass;
	position = Vec2(x, y);
}

void CollisionObject::updatePosition(double deltaTime, double gravity) {
	acceleration = force / mass + Vec2(0.0, useGravity ? gravity : 0.0);
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

