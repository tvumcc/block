#pragma once
#include "collision_object.hpp"

class Collision {
public:
	CollisionObject* a;
	CollisionObject* b;

	// If true, then the two objects are intersecting
	bool collides;

	// The "direction" of the collision
	Vec2 normal;

	// How far one object is inside the other
	double depth;

	Collision(CollisionObject* a, CollisionObject* b);

	//  Determines whether the two objects are intersecting while computing other values necessary for collision resolution
	void computeCollision();

	// Performs collision resolution, updating the two objects' position and velocity
	void resolve();
private:
	// Computes the collision between two Rectangle objects
	void Rectangle_vs_Rectangle();
};
