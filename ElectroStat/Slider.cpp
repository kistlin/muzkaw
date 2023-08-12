#include "Slider.h"

Slider::Slider(sf::Vector2f bodySize, sf::Vector2f sliderSize, sf::Vector2f position, float min, float max,
               std::string text, sf::Font& font) {
	m_body = sf::RectangleShape(bodySize);
	m_slider = sf::RectangleShape(sliderSize);
	m_body.setFillColor(sf::Color::Blue);
	m_body.setOutlineColor(sf::Color::Black);
	m_body.setOutlineThickness(3);
	m_slider.setFillColor(sf::Color::White);
	m_slider.setOutlineColor(sf::Color::Black);
	m_slider.setOutlineThickness(3);

	m_textPosition = position;
	m_text.setFont(font);
	m_text.setPosition(position);
	m_text.setCharacterSize(15);
	m_text.setString(text);
	m_text.setColor(sf::Color::Black);
	m_initialText = text;

	m_position = m_text.findCharacterPos(m_text.getString().getSize() - 1) + sf::Vector2f(40, 5);
	m_body.setPosition(m_position);
	m_slider.setPosition(
	    sf::Vector2f(m_position.x + (bodySize.x - sliderSize.x) / 2, m_position.y - (sliderSize.y - bodySize.y) / 2));
	m_wasClicked = false;
	m_min = min;
	m_max = max;

	std::ostringstream oss;
	oss << getSliderValue();
	m_text.setString(m_initialText + oss.str());
}

bool Slider::isSliderClicked(sf::Mouse::Button button, sf::Vector2f mousePos) {
	if ((m_slider.getGlobalBounds().contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) ||
	    m_wasClicked) {
		m_slider.setPosition(mousePos.x + -m_slider.getSize().x / 2, m_slider.getPosition().y);

		if (m_slider.getPosition().x >=
		    m_body.getPosition().x + m_body.getSize().x - m_slider.getSize().x)  // boundings
			m_slider.setPosition(sf::Vector2f(m_body.getPosition().x + m_body.getSize().x - m_slider.getSize().x,
			                                  m_slider.getPosition().y));
		if (m_slider.getPosition().x <= m_body.getPosition().x)
			m_slider.setPosition(sf::Vector2f(m_body.getPosition().x, m_slider.getPosition().y));

		m_wasClicked = true;
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			m_wasClicked = false;

		std::ostringstream oss;
		oss << getSliderValue();
		m_text.setString(m_initialText + oss.str());
	}
	else
		return false;
}

int Slider::getSliderValue() {
	return ((m_slider.getPosition().x - m_position.x) / (m_body.getSize().x - m_slider.getSize().x) - 0.5) *
	           (m_max - m_min) +
	       (m_max + m_min) / 2;
}
void Slider::setText(sf::Font& font, std::string text, int size) {
	m_text.setFont(font);
	m_text.setPosition(m_textPosition);
	m_text.setCharacterSize(size);
	m_text.setString(text);
	m_text.setColor(sf::Color::Black);
}

void Slider::draw(sf::RenderWindow& window) {
	window.draw(m_body);
	window.draw(m_slider);
	window.draw(m_text);
}
