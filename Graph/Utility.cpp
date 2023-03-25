#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>

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

sf::Vector2f Normalize(sf::Vector2f const& v) {
	return v / Norm(v);
}

float rest(float const& a, float const& b) {
	return a - floor(a / b) * b;
}

bool mouseClickedOnce(sf::Mouse::Button const& button, bool& clickBuffer) {
	bool result = false;
	if (sf::Mouse::isButtonPressed(button) && clickBuffer == false) {
		result = true;
		clickBuffer = true;
	}
	else if (sf::Mouse::isButtonPressed(button) && clickBuffer == true) {
		result = false;
		clickBuffer = true;
	}
	else {
		result = false;
		clickBuffer = false;
	}
	return result;
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
	line[1].position = dir + pos;
	line[1].color = color;
	window.draw(line);
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
float minClamp(float value, float min) {
	float result;
	if (value < min)
		result = min;
	else
		result = value;
	return result;
}
float maxClamp(float value, float max) {
	float result;
	if (value > max)
		result = max;
	else
		result = value;
	return result;
}

bool checkSegmentIntersection(sf::Vector2f const& A, sf::Vector2f const& B, sf::Vector2f const& C,
                              sf::Vector2f const& D) {
	if (determinant(B - A, C - A) * determinant(B - A, D - A) < 0 &&
	    determinant(D - C, A - C) * determinant(D - C, B - C) < 0)
		return true;
	return false;
}
bool collisionTrianglePoint(sf::Vector2f const& a, sf::Vector2f const& b, sf::Vector2f const& c,
                            sf::Vector2f const& point) {
	sf::Vector2f ab = b - a;
	sf::Vector2f bc = c - b;
	sf::Vector2f ca = a - c;

	if (determinant(ab, point - a) > 0 && determinant(bc, point - b) > 0 && determinant(ca, point - c) > 0) {
		return true;
	}
	else
		return false;
}

sf::Vector2f randVector2f(float const& among) {
	return sf::Vector2f((rand() % RAND_MAX / (float)RAND_MAX - 0.5) * among,
	                    (rand() % RAND_MAX / (float)RAND_MAX - 0.5) * among);
}

sf::Text textSettings(std::string const& text, float const& size, sf::Color const& color, sf::Font const& font,
                      sf::Vector2f const& position) {
	sf::Text txt;
	txt.setCharacterSize(size);
	txt.setColor(color);
	txt.setFont(font);
	txt.setString(text);
	txt.setPosition(position);
	return txt;
}

std::vector<std::string> readCfgFile(std::string path) {
	std::ifstream cfg(path);
	std::string line;
	std::vector<std::string> result;
	std::string dataBuf;
	std::string strBuf;

	cfg >> strBuf >> dataBuf;
	result.push_back(dataBuf);

	while (getline(cfg, line)) {
		cfg.ignore();
		cfg >> strBuf >> dataBuf;
		result.push_back(dataBuf);
	}
	result.erase(result.end() - 1);
	return result;
}
