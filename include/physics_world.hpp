#pragma once
#include <vector>

#include "collision.hpp"
#include "collision_object.hpp"
#include "rectangle.hpp"

class PhysicsWorld {
public:
	// Boundary Blocks
	Rectangle leftWall;
	Rectangle rightWall;
	Rectangle topWall;
	Rectangle botWall;
	
	// Changing these values can increase the accuracy of the simulation while decreasing performance
	int stepsPerFrame;
	double deltaTimeDivisor;

	// Acceleration due to gravity in m/s^2
	const double gravity = 9.81;

	// Stores collision pairs to be resolved
	std::vector<Collision> collisions;

	// Stores pointers to objects which exist inside this physics context
	std::vector<CollisionObject*> objs;
	
	// Initializes a physics context using the dimensions of the window
	PhysicsWorld(double windowWidth, double windowHeight, int stepsPerFrame, double deltaTimeDivisor);

	// Initializes the world boundaries using the dimensions of the window
	void setupBounds(double windowWidth, double windowHeight);

	// Updates all objects positions and resolves collisions, deltaTime must be in milliseconds
	void update(double deltaTime);

	// Iterates through all pairs of objects to find collisions, 
	void detectCollisions();

	// Adds an object to the physics context
	void addObject(CollisionObject* obj);

	// Explodes a rectangle into n by m pieces
	void explodeRect(CollisionObject* rectangle, int n, int m);

	// Draws all visible objects to a SFML RenderWindow
	void drawObjects(sf::RenderWindow& window);
};
