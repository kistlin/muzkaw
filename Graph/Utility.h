#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <vector>

#define PI 3.14159265359

float determinant(sf::Vector2f const& u, sf::Vector2f const& v);
float dotProduct(sf::Vector2f const& u, sf::Vector2f const& v);
float Angle(sf::Vector2f const& v1, sf::Vector2f const& v2);
float Distance(sf::Vector2f const& u, sf::Vector2f const& v);
sf::Vector2f rotatePoint(sf::Vector2f const& point, sf::Vector2f const& center, float const& angle);
float Norm(sf::Vector2f const& v);
sf::Vector2f Normalize(sf::Vector2f const& v);
float rest(float const& a, float const& b);

bool mouseClickedOnce(sf::Mouse::Button const& button, bool& clickBuffer);
void drawPoint(sf::Vector2f const& p, float const& radius, sf::RenderWindow& window, sf::Color const& color);
void drawLine(sf::Vector2f const& pos, sf::Vector2f const& dir, sf::RenderWindow& window, sf::Color const& color);

float clamp(float value, float min, float max);
float minClamp(float value, float min);
float maxClamp(float value, float max);
bool checkSegmentIntersection(sf::Vector2f const& A, sf::Vector2f const& B, sf::Vector2f const& C,
                              sf::Vector2f const& D);
bool collisionTrianglePoint(sf::Vector2f const& a, sf::Vector2f const& b, sf::Vector2f const& c,
                            sf::Vector2f const& point);
sf::Vector2f randVector2f(float const& among);

sf::Text textSettings(std::string const& text, float const& size, sf::Color const& color, sf::Font const& font,
                      sf::Vector2f const& position);

std::vector<std::string> readCfgFile(std::string path);
