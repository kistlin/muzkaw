#pragma once

#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <sstream>

class Slider {
public:
	Slider();
	Slider(sf::Vector2f _position, std::string _text, sf::Font* font, sf::RenderWindow* _window, float _value = 0,
	       float _min = 0, float _max = 0);

	void update();
	float getSliderValue();
	void setSliderValue(float const& x);

	bool wasModified();

	void draw();

private:
	float value;

	sf::Vector2f position;
	sf::Vector2f mousePos;
	sf::Vector2f prevMousePos;
	sf::Clock deltaTime;
	float dt;
	sf::Clock click;

	sf::Event event;
	bool edit1, edit2;
	bool modified;
	bool flag;
	bool onExit;

	float min;
	float max;

	sf::Text text;
	std::string initialText;
	std::string str;
	sf::RenderWindow* window;
};
