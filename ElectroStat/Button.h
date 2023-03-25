#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::RectangleShape {
public:
	Button(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string text, sf::Color color,
	       bool initialCondition);
	bool isButtonClicked(sf::Mouse::Button button, sf::Vector2f mousePos, bool mouseClickedLastFrame);
	void switchButton();
	void setText(sf::Font& font, std::string text, int size);

	bool getCondition();

	void draw(sf::RenderWindow& window);

private:
	bool m_condition;
	sf::Text m_text;
	sf::Color m_color;
};
