#pragma once
#include "Charge.h"
#include "Point.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define PI 3.14159265359

void interpolation(float& x, float const& y, float const& time, float const& deltaTime);
float determinant(sf::Vector2f const& u, sf::Vector2f const& v);
float dotProduct(sf::Vector2f const& u, sf::Vector2f const& v);
float Angle(sf::Vector2f const& v1, sf::Vector2f const& v2);
int interpolation(int& x, int const& y, float const& time, float const& deltaTime);
void drawPoint(sf::Vector2f const& p, float const& radius, sf::RenderWindow& window, sf::Color const& color);
void drawLine(sf::Vector2f const& pos, sf::Vector2f const& dir, sf::RenderWindow& window, sf::Color const& color);
float Distance(sf::Vector2f const& u, sf::Vector2f const& v);
sf::Vector2f rotatePoint(sf::Vector2f const& point, sf::Vector2f const& center, float const& angle);
float Norm(sf::Vector2f const& v);
bool mouseClickedOnce(sf::Mouse::Button const& button, bool& clickedLastFrame);
float clamp(float value, float min, float max);