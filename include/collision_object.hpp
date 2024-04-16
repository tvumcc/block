#pragma once
#include <SFML/Graphics.hpp>
#include "vec2.hpp"

enum class CollisionShape {
	None,
	Rectangle
};

class CollisionObject {
public:
	// Mass of the object in kilograms
	double mass;

	// Determines the elasticity of the object. See: https://en.wikipedia.org/wiki/Coefficient_of_restitution
	double restitution;

	// Flag for acceleration due to gravity on this object
	bool useGravity;

	// Flag for preventing the movement of this object
	bool isStatic;

	// Flag for drawing the object to the screen
	bool visible;

	// Flag for allowing explosion of this object
	bool explodable;

	sf::Color color;

	// Determines the shape of this object
	CollisionShape shape;

	// Vectors to describe the object's state in the physics world
	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
	Vec2 force;
	Vec2 impulse;


	CollisionObject();
	CollisionObject(double x, double y, double mass);

	// Update the object position using semi-implicit Euler integration
	void updatePosition(double deltaTime, double gravity);

	void addForce(Vec2 v);
	void addImpulse(Vec2 v);
	void resetForceImpulse();

	// Draw this object to a SFML RenderWindow
	virtual void draw(sf::RenderWindow& window) = 0;
};
