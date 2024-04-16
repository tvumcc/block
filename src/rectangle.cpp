#include "rectangle.hpp"

Rectangle::Rectangle() {
	this->width = 1.0;
	this->height = 1.0;
	shape = CollisionShape::Rectangle;
}

Rectangle::Rectangle(double x, double y, double mass, double width, double height) {
	this->position = Vec2(x, y);

	this->mass = mass;
	this->width = width;
	this->height = height;
	shape = CollisionShape::Rectangle;
}

void Rectangle::draw(sf::RenderWindow& window) {
	sf::RectangleShape rect = sf::RectangleShape(sf::Vector2<float>(width,height));
	rect.setFillColor(color);
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(-1.0f);
	rect.setPosition(sf::Vector2<float>(position.x - width/2.0, position.y - height/2.0));
	window.draw(rect);
}
