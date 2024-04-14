#include "collision_object.hpp"

CollisionObject::CollisionObject() {}

CollisionObject::CollisionObject(double x, double y, double r, double g, double b, double mass) 
	: impulse(Vec2(0.0, 0.0)), force(Vec2(0.0, 0.0)), acceleration(Vec2(0.0, 0.0)), velocity(Vec2(0.0, 0.0)), position(Vec2(x, y))
{
	this->mass = mass;

	red = r;
	green = g;
	blue = b;
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
	force = Vec2(0.0, 0.0);
	impulse = Vec2(0.0, 0.0);
}

void CollisionObject::draw(sf::RenderWindow& window) {
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2<float>(100,100));
	rect.setFillColor(sf::Color(red, green , blue));
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(2.0f);
	rect.setPosition(sf::Vector2<float>(position.x, position.y));
	window.draw(rect);
}
