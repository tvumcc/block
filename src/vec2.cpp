#include <cmath>

#include "vec2.hpp"

Vec2::Vec2(double x, double y) {
	this->x = x;
	this->y = y;
}

Vec2::Vec2() {
	this->x = 0.0;
	this->y = 0.0;
}

void Vec2::normalize() {
	double hyp = len(*this);
	x /= hyp;
	y /= hyp;
}

void Vec2::operator+=(Vec2 v) {
	this->x += v.x;
	this->y += v.y;
}

void Vec2::operator-=(Vec2 v) {
	this->x -= v.x;
	this->y -= v.y;
}

void Vec2::operator*=(double scalar) {
	this->x *= scalar;
	this->y *= scalar;
}

void Vec2::operator/=(double scalar) {
	this->x /= scalar;
	this->y /= scalar;
}


Vec2 operator*(double scalar, Vec2 v) {return Vec2(v.x * scalar, v.y * scalar);}
Vec2 operator*(Vec2 v, double scalar) {return Vec2(v.x * scalar, v.y * scalar);}
Vec2 operator/(double scalar, Vec2 v) {return Vec2(v.x / scalar, v.y / scalar);}
Vec2 operator/(Vec2 v, double scalar) {return Vec2(v.x / scalar, v.y / scalar);}

Vec2 operator+(Vec2 a, Vec2 b) {return Vec2(a.x + b.x, a.y + b.y);}
Vec2 operator-(Vec2 a, Vec2 b) {return Vec2(a.x - b.x, a.y - b.y);}

double len(Vec2 v) {return sqrt(v.x * v.x + v.y * v.y);}
double operator*(Vec2 a, Vec2 b) {return a.x * b.x + a.y * b.y;}
double operator^(Vec2 a, Vec2 b) {return -a.y * b.x + a.x * b.y;}
