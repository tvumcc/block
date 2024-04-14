#pragma once
#include <SFML/Graphics.hpp>
#include "vec2.hpp"

class CollisionObject {
public:
	double mass;

	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
	Vec2 force;
	Vec2 impulse;

	double red;
	double blue;
	double green;

	CollisionObject();
	CollisionObject(double x, double y, double r, double g, double b, double mass);

	// Update the object position using semi-implicit Euler integration
	void updatePosition(double deltaTime);
	void addForce(Vec2 v);
	void addImpulse(Vec2 v);
	void resetForceImpulse();

	void draw(sf::RenderWindow& window);
	void setColor(double r, double g, double b);


};
