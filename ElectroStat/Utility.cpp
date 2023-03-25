#include "Utility.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <cmath>

void interpolation(float& x, float const& y, float const& time, float const& deltaTime) {
	x += (2.f * (y - x) * deltaTime) / time;
}

float determinant(sf::Vector2f const& u, sf::Vector2f const& v) {
	float result = u.x * v.y - u.y * v.x;
	return result;
}

float dotProduct(sf::Vector2f const& u, sf::Vector2f const& v) {
	return u.x * v.x + u.y * v.y;
}

float Angle(sf::Vector2f const& v1, sf::Vector2f const& v2) {
	float angle = atan2(determinant(v1, v2), dotProduct(v1, v2)) * 180 / PI;
	if (angle < 0)
		angle = 360 + angle;
	return angle;
}

void drawPoint(sf::Vector2f const& p, float const& radius, sf::RenderWindow& window, sf::Color const& color) {
	sf::CircleShape c(radius);
	c.setFillColor(color);
	c.setPosition(p);
	c.setOrigin(radius, radius);
	window.draw(c);
}

void drawLine(sf::Vector2f const& pos, sf::Vector2f const& dir, sf::RenderWindow& window, sf::Color const& color) {
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = pos;
	line[0].color = color;
	line[1].position = dir;
	line[1].color = color;
	window.draw(line);
}

float Distance(sf::Vector2f const& u, sf::Vector2f const& v) {
	return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2));
}

sf::Vector2f rotatePoint(sf::Vector2f const& point, sf::Vector2f const& center, float const& angle) {
	float x =
	    center.x + (point.x - center.x) * cos(angle * (PI / 180)) - (point.y - center.y) * sin(angle * (PI / 180));
	float y =
	    center.y + (point.x - center.x) * sin(angle * (PI / 180)) + (point.y - center.y) * cos(angle * (PI / 180));
	return sf::Vector2f(x, y);
}

float Norm(sf::Vector2f const& v) {
	float result = sqrt(pow(v.x, 2) + pow(v.y, 2));
	return result;
}

bool mouseClickedOnce(sf::Mouse::Button const& button, bool& clickedLastFrame) {
	bool result = false;
	if (sf::Mouse::isButtonPressed(button) && clickedLastFrame == false) {
		result = true;
		clickedLastFrame = true;
	}
	else if (sf::Mouse::isButtonPressed(button) && clickedLastFrame == true) {
		result = false;
		clickedLastFrame = true;
	}
	else {
		result = false;
		clickedLastFrame = false;
	}
	return result;
}

float clamp(float value, float min, float max) {
	float result;
	if (value > max)
		result = max;
	else if (value < min)
		result = min;
	else
		result = value;
	return result;
}
