#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

float Distance(sf::Vector2f const& v1, sf::Vector2f const& v2);
float Norm(sf::Vector2f const& u);
sf::Vector2f Normalize(sf::Vector2f u);

sf::Vector2f randVector2f(sf::Vector2f const& min, sf::Vector2f const& max);

bool mouseClickedOnce(sf::Mouse::Button const& button, bool& clickedLastFrame);