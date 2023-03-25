#include "Button.h"
#include "Utility.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font& font, std::string text, sf::Color color,
               bool initialCondition) {
	m_text.setFont(font);
	m_text.setPosition(position);
	m_text.setCharacterSize(15);
	m_text.setString(text);
	m_text.setColor(sf::Color::Black);
	setSize(size);
	setPosition(m_text.findCharacterPos(m_text.getString().getSize() - 1) + sf::Vector2f(10, 0));
	setOutlineThickness(3);
	setOutlineColor(sf::Color::Black);
	m_color = color;
	m_condition = initialCondition;
}

bool Button::isButtonClicked(sf::Mouse::Button button, sf::Vector2f mousePos, bool mouseClickedLastFrame) {
	if (getGlobalBounds().contains(mousePos) && mouseClickedOnce(sf::Mouse::Left, mouseClickedLastFrame)) {
		switchButton();
		return true;
	}
	else
		return false;
}

void Button::switchButton() {
	m_condition = !m_condition;
}

void Button::setText(sf::Font& font, std::string text, int size) {
	m_text.setFont(font);
	m_text.setPosition(getPosition());
	m_text.setCharacterSize(size);
	m_text.setString(text);
	m_text.setColor(sf::Color::Black);
}

bool Button::getCondition() {
	return m_condition;
}

void Button::draw(sf::RenderWindow& window) {
	if (m_condition)
		setFillColor(m_color);
	else
		setFillColor(sf::Color::White);
	window.draw(*this);
	window.draw(m_text);
}