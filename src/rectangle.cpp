#include "rectangle.hpp"
#include <iostream>

Rectangle::Rectangle() {
	this->width = 1.0;
	this->height = 1.0;
}

Rectangle::Rectangle(double width, double height) {
	this->width = width;
	this->height = height;
}

void Rectangle::draw(sf::RenderWindow& window) {
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2<float>(width,height));
	rect.setFillColor(sf::Color((int)red, (int)green, (int)blue));
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(2.0f);
	rect.setPosition(sf::Vector2<float>(position.x - width/2.0, position.y - height/2.0));
	window.draw(rect);
}

Collision::Collision(Rectangle* a, Rectangle* b) {
	this->a = a;
	this->b = b;

	computeCollision();
}

void Collision::computeCollision() {
	double a_min_x = a->position.x - (a->width / 2.0);
	double a_max_x = a->position.x + (a->width / 2.0);
	double a_min_y = a->position.y - (a->height / 2.0);
	double a_max_y = a->position.y + (a->height / 2.0);

	double b_min_x = b->position.x - (b->width / 2.0);
	double b_max_x = b->position.x + (b->width / 2.0);
	double b_min_y = b->position.y - (b->height / 2.0);
	double b_max_y = b->position.y + (b->height / 2.0);

	collides = (a_min_x <= b_max_x) && (a_max_x >= b_min_x) && (a_min_y <= b_max_y) && (a_max_y >= b_min_y);

	if (collides) {

		if (abs(a_min_x - b_max_x) > abs(a_max_x - b_min_x)) {
			normal.x = b_min_x - a_max_x;
		} else normal.x = a_min_x - b_max_x;

		if (abs(a_min_y - b_max_y) > abs(a_max_y - b_min_y)) {
			normal.y = b_min_y - a_max_y;		
		} else normal.y = a_min_y - b_max_y;

		double num = 0.0;
		if (abs(normal.y) < abs(normal.x)) num = normal.y;
		else num = normal.x;

		normal = (a->position - b->position);
		normal.normalize();

		depth = len(normal * num);

		std::cout << "normal x: " << normal.x << " y: " << normal.y << " depth: " << depth << std::endl;
	}
}

void Collision::resolve() {
	if (collides) {
		double j = ((-(1.0 + (a->e + b->e) / 2.0) * (a->velocity - b->velocity)) * normal) / (1.0 / a->mass + 1.0 / b->mass);

		a->addImpulse(j * normal);
		b->addImpulse(-j * normal);
	}
}
