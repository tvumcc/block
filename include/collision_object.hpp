#pragma once
#include <SFML/Graphics.hpp>
#include "vec2.hpp"

enum class CollisionShape {
	None,
	Rectangle
};

class CollisionObject {
public:
	double mass;
	double restitution;
	bool useGravity;
	bool isStatic;
	CollisionShape shape;

	Vec2 position;
	Vec2 velocity;
	Vec2 acceleration;
	Vec2 force;
	Vec2 impulse;

	sf::Color color;

	CollisionObject();
	CollisionObject(double x, double y, double mass);

	// Update the object position using semi-implicit Euler integration
	void updatePosition(double deltaTime);

	void addForce(Vec2 v);
	void addImpulse(Vec2 v);
	void resetForceImpulse();

	virtual void draw(sf::RenderWindow& window) = 0;
};

class Collision {
public:
	CollisionObject* a;
	CollisionObject* b;
	bool collides;
	Vec2 normal;
	double depth;

	Collision(CollisionObject* a, CollisionObject* b);
	void resolve();
	void computeCollision();

	void Rectangle_vs_Rectangle();
};
