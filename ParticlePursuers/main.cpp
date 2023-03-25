// check https://www.youtube.com/watch?v=OoZv0yLRQWc for explanation and controls -Muzkaw

#include "Particle.h"
#include "Slider.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>

int main() {
	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(900, 900, 32), "Window");

	std::vector<Particle> particle;

	sf::Clock deltaTime;
	float dt = 0.1;
	int a;
	sf::Vector2f mousePos;
	sf::Font font;
	font.loadFromFile("consola.ttf");

	std::vector<Slider> slider;
	slider.push_back(Slider(sf::Vector2f(20, 40), "Mass : ", &font, &window, 1, 0, 10));
	slider.push_back(Slider(sf::Vector2f(20, 60), "Force : ", &font, &window, 2e6, 1e5, 1e9));
	slider.push_back(Slider(sf::Vector2f(20, 80), "Drag : ", &font, &window, 3.7, 0, 5));
	slider.push_back(Slider(sf::Vector2f(20, 100), "Number : ", &font, &window, 200, 0, 1000));
	slider.push_back(Slider(sf::Vector2f(20, 120), "Force Pow : ", &font, &window, 1.04, 0, 4));
	slider.push_back(Slider(sf::Vector2f(20, 140), "Drag Pow : ", &font, &window, 1.44, 0, 4));
	slider.push_back(Slider(sf::Vector2f(20, 160), "Min Dist : ", &font, &window, 54, 0, 100));

	while (true) {
		int nb = slider[3].getSliderValue();
		particle.clear();
		for (int i(0); i < nb; i++)
			particle.push_back(
			    Particle(slider[0].getSliderValue(),
			             sf::Vector2f(450, 450) + randVector2f(sf::Vector2f(-300, -300), sf::Vector2f(300, 300)),
			             sf::Color::Color(255, i / (float)nb * 255, 0)));

		float force = slider[1].getSliderValue();
		float drag = slider[2].getSliderValue();

		while (window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			for (int i(0); i < slider.size(); i++)
				slider[i].update();

			if (slider[0].wasModified())
				for (int i(0); i < particle.size(); i++)
					particle[i].setMass(slider[0].getSliderValue());
			if (slider[1].wasModified())
				force = slider[1].getSliderValue();
			if (slider[2].wasModified())
				drag = slider[2].getSliderValue();

			mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

			for (int i(0); i < particle.size(); i++) {
				if (i == particle.size() - 1)
					a = 0;
				else
					a = i + 1;
				particle[i].addForce(force * Normalize(particle[a].getPosition() - particle[i].getPosition()) /
				                     pow(std::max(Distance(particle[a].getPosition(), particle[i].getPosition()),
				                                  slider[6].getSliderValue()),
				                         slider[4].getSliderValue()));
				particle[i].addForce(-drag * Normalize(particle[i].getSpeed()) *
				                     pow(std::max(Norm(particle[i].getSpeed()), 1.f), slider[5].getSliderValue()));
				particle[i].updatePosition(dt);
				particle[i].clearForce();
			}

			particle.back().setPosition(mousePos);

			window.clear();
			for (int i(0); i < particle.size() - 1; i++)
				particle[i].draw(window);
			for (int i(0); i < slider.size(); i++)
				slider[i].draw();
			window.display();

			dt = deltaTime.restart().asSeconds();
		}
	}
}