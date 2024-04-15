#pragma once
#include "collision_object.hpp"

class Rectangle : public CollisionObject {
public:
	double width;
	double height;
	
	Rectangle();
	Rectangle(double x, double y, double mass, double width, double height);
	void draw(sf::RenderWindow& window);
};

