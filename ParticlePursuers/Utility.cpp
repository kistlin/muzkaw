#include "Utility.h"

float Distance(sf::Vector2f const& v1, sf::Vector2f const& v2) {
	return sqrt(pow((v2.x - v1.x), 2) + pow((v2.y - v1.y), 2));
}
float Norm(sf::Vector2f const& u) {
	return sqrt(pow(u.x, 2) + pow(u.y, 2));
}
sf::Vector2f Normalize(sf::Vector2f u) {
	if (Norm(u) != 0)
		return u / (float)Norm(u);
	else
		return sf::Vector2f(0, 0);
}
sf::Vector2f randVector2f(sf::Vector2f const& min, sf::Vector2f const& max) {
	return sf::Vector2f((float)(rand() / (float)RAND_MAX) * (max.x - min.x) + min.x,
	                    (float)(rand() / (float)RAND_MAX) * (max.y - min.y) + min.y);
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