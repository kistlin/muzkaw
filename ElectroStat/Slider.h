#pragma once

#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <sstream>

class Slider {
public:
	Slider(sf::Vector2f bodySize, sf::Vector2f sliderSize, sf::Vector2f position, float min, float max,
	       std::string text, sf::Font& font);

	bool isSliderClicked(sf::Mouse::Button button, sf::Vector2f mousePos);
	int getSliderValue();
	void setText(sf::Font& font, std::string text, int size);

	void draw(sf::RenderWindow& window);

private:
	sf::RectangleShape m_body;
	sf::RectangleShape m_slider;
	sf::Vector2f m_position;
	sf::Vector2f m_textPosition;
	bool m_wasClicked;
	float m_min;
	float m_max;
	sf::Text m_text;
	std::string m_initialText;
};
