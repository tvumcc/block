#pragma once


class Vec2 {
public:
	double x;
	double y;

	Vec2();
	Vec2(double x, double y);

	void normalize();
	void operator+=(Vec2 v);
	void operator-=(Vec2 v);
	void operator*=(double scalar);
	void operator/=(double scalar);
};

// Compute the dot product between two vectors
double operator*(Vec2 a, Vec2 b);

// Compute the perpdot product between two vectors
// See: https://mathworld.wolfram.com/PerpDotProduct.html
double operator^(Vec2 a, Vec2 b);

double len(Vec2 v);

// Multiplicative operations by a scalar
Vec2 operator*(double scalar, Vec2 v);
Vec2 operator*(Vec2 v, double scalar);
Vec2 operator/(double scalar, Vec2 v);
Vec2 operator/(Vec2 v, double scalar);

// Additive operations
Vec2 operator+(Vec2 a, Vec2 b);
Vec2 operator-(Vec2 a, Vec2 b);
