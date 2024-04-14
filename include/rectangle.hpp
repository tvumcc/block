#pragma once
#include "collision_object.hpp"

class Rectangle : public CollisionObject {
public:
	double width;
	double height;
	double e;
	
	Rectangle();
	Rectangle(double width, double height);
	void draw(sf::RenderWindow& window);
};

class Collision {
public:
	Rectangle* a;
	Rectangle* b;
	bool collides;
	Vec2 normal;
	double depth;

	Collision(Rectangle* a, Rectangle* b);
	void resolve();
	void computeCollision();
};
