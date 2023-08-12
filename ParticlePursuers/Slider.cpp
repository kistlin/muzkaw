#include "Slider.h"

Slider::Slider() {
}

Slider::Slider(sf::Vector2f _position, std::string _text, sf::Font* font, sf::RenderWindow* _window, float _value,
               float _min, float _max) {
	window = _window;

	text.setFont(*font);
	text.setPosition(_position);
	text.setCharacterSize(13);
	text.setString(_text);
	text.setColor(sf::Color::White);
	initialText = _text;

	position = _position + sf::Vector2f(0, 16);

	edit1 = false;
	edit2 = false;
	modified = false;
	flag = false;
	onExit = false;
	min = _min;
	max = _max;

	value = _value;
	setSliderValue(value);

	dt = 0.01;
}

void Slider::update() {
	prevMousePos = mousePos;
	mousePos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
	if (prevMousePos.x != mousePos.x && (edit1 || edit2)) {
		modified = true;
		dt = deltaTime.restart().asSeconds();
	}
	else
		modified = false;
	onExit = false;

	if (text.getGlobalBounds().contains(mousePos) && mouseClickedOnce(sf::Mouse::Left, flag)) {
		edit1 = true;
		if (click.restart().asSeconds() < 0.3) {
			edit2 = true;
			edit1 = false;
		}
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
		edit1 = false;
	if (!text.getGlobalBounds().contains(mousePos) && mouseClickedOnce(sf::Mouse::Left, flag) && edit2) {
		edit2 = false;
		onExit = true;
	}

	if (edit1) {
		// sf::Mouse::setPosition(Vector2i(position.x,position.y),*window) ;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			value += (max - min) * (mousePos.x - prevMousePos.x) / 1000.f;
		else
			value += (max - min) * (mousePos.x - prevMousePos.x) / 100.f;

		setSliderValue(value);

		text.setColor(sf::Color(100, 200, 20));
	}

	else if (edit2) {
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::TextEntered) {
				if (event.text.unicode < 128 && event.text.unicode != 8)
					str += static_cast<char>(event.text.unicode);
				if (event.text.unicode == 8 && str.size() > 0)
					str.pop_back();
				// modified = true ;
			}
		}

		text.setString(initialText + str);
		text.setColor(sf::Color(200, 20, 100));
	}
	else
		text.setColor(sf::Color::White);
	if (onExit) {
		setSliderValue(stof(str));
		modified = true;
	}
}

float Slider::getSliderValue() {
	return value;
}
void Slider::setSliderValue(float const& x) {
	value = x;

	if (min != max) {
		if (value > max)  // boundings
			value = max;
		if (value < min)
			value = min;
	}
	std::ostringstream oss;
	oss << value;
	text.setString(initialText + oss.str());
}

bool Slider::wasModified() {
	return modified;
}

void Slider::draw() {
	window->draw(text);
}
