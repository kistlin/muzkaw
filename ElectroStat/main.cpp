/* Electric fiel visualization codded by Muzkaw : https://www.youtube.com/user/Muzkaw
   Feel free to use it for whatever application
   It shows the lectric field lines created by punctual charges. Continuous materials can be mimicked by stacking
   multiple charges close one to another (eg capacitor) You need to link SFML 2.0 or above to run the program Happy
   coding ! */

#include "Button.h"
#include "Charge.h"
#include "Point.h"
#include "Slider.h"
#include "Utility.h"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>

#define SCR_WIDTH 1100
#define SCR_HEIGHT 900

#define MENU_WIDTH 250

#define SGMT_LENGTH 10
#define SGMT_NB 100

#define E_FIELD_NUMBER 50
#define V_FIELD_NUMBER 300

int main() {
	sf::RenderWindow window(sf::VideoMode(SCR_WIDTH, SCR_HEIGHT), "ElectroStat");  // window
	window.setFramerateLimit(80);

	std::vector<Charge> charges;  // field lines
	sf::VertexArray EFieldVA(sf::Lines);
	std::vector<sf::VertexArray> EFieldLinesVA(sf::LinesStrip);
	std::vector<float> VField;

	std::vector<sf::Vector2f> wallPoints;  // walls
	wallPoints.push_back(sf::Vector2f(MENU_WIDTH, 0));
	wallPoints.push_back(sf::Vector2f(MENU_WIDTH + 1, SCR_HEIGHT));
	wallPoints.push_back(sf::Vector2f(MENU_WIDTH + 1, SCR_HEIGHT));
	wallPoints.push_back(sf::Vector2f(SCR_WIDTH, SCR_HEIGHT + 1));
	wallPoints.push_back(sf::Vector2f(SCR_WIDTH, SCR_HEIGHT + 1));
	wallPoints.push_back(sf::Vector2f(SCR_WIDTH - 1, 0));
	wallPoints.push_back(sf::Vector2f(SCR_WIDTH - 1, 0));
	wallPoints.push_back(sf::Vector2f(MENU_WIDTH, 0));

	sf::RectangleShape menuBackground;
	menuBackground.setSize(sf::Vector2f(MENU_WIDTH, SCR_HEIGHT));
	menuBackground.setFillColor(sf::Color::Color(210, 210, 210));  // menu
	menuBackground.setOutlineColor(sf::Color::Black);
	menuBackground.setOutlineThickness(5);
	sf::Font arial;
	arial.loadFromFile("arial.ttf");

	Button EFieldButton(sf::Vector2f(20, 140), sf::Vector2f(20, 20), arial, "Draw electric field : ", sf::Color::Blue,
	                    false);
	Button drawNegativeLinesButton(sf::Vector2f(20, 170), sf::Vector2f(20, 20), arial,
	                               "Draw all field lines : ", sf::Color::Blue, false);
	Button movingChargeButton(sf::Vector2f(20, 200), sf::Vector2f(20, 20), arial, "Moving charge : ", sf::Color::Blue,
	                          true);

	Slider chargeSlider(sf::Vector2f(100, 10), sf::Vector2f(10, 20), sf::Vector2f(20, 20), -10, 10, "Charge : ", arial);
	Slider massSlider(sf::Vector2f(100, 10), sf::Vector2f(10, 20), sf::Vector2f(20, 50), 1, 1000, "Mass : ", arial);
	Slider fieldLinesSlider(sf::Vector2f(100, 10), sf::Vector2f(10, 20), sf::Vector2f(20, 80), 0, 30,
	                        "Field lines : ", arial);
	Slider VQualitySlider(sf::Vector2f(100, 10), sf::Vector2f(10, 20), sf::Vector2f(20, 110), 0, 6,
	                      "V quality : ", arial);

	sf::Clock deltaTime;  // time
	sf::Clock time;
	float dt = 0.001;

	sf::Image image;  // TODO: size increased, else out of bound access
	image.create(SCR_WIDTH - MENU_WIDTH + 3, SCR_HEIGHT + 3, sf::Color::Black);
	sf::Texture texture;
	texture.setSmooth(true);
	sf::Sprite sprite(texture);
	sprite.setPosition(MENU_WIDTH, 0);

	bool mouseClickedLastFrame = false;  // mouse

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		sf::Vector2f mousePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		EFieldButton.isButtonClicked(sf::Mouse::Left, mousePos, mouseClickedLastFrame);
		movingChargeButton.isButtonClicked(sf::Mouse::Left, mousePos, mouseClickedLastFrame);
		drawNegativeLinesButton.isButtonClicked(sf::Mouse::Left, mousePos, mouseClickedLastFrame);
		chargeSlider.isSliderClicked(sf::Mouse::Left, mousePos);
		massSlider.isSliderClicked(sf::Mouse::Left, mousePos);
		fieldLinesSlider.isSliderClicked(sf::Mouse::Left, mousePos);
		VQualitySlider.isSliderClicked(sf::Mouse::Left, mousePos);

		if (mouseClickedOnce(sf::Mouse::Left, mouseClickedLastFrame)) {
			if (mousePos.x > MENU_WIDTH) {
				Charge c(chargeSlider.getSliderValue(), massSlider.getSliderValue(), mousePos);
				if (!movingChargeButton.getCondition())
					c.setStatic();
				charges.push_back(c);
			}
		}

		for (int i(0); i < charges.size(); i++) {
			sf::Vector2f previousPosition = charges[i].getPosition();
			if (charges[i].isMovable())
				charges[i].updatePosition(dt);
			charges[i].clearForce();
			for (int j(0); j < charges.size(); j++) {
				if (j != i)
					charges[i].addForce(charges[i].getCoulombForce(charges[j]));
			}
			for (int j(0); j < wallPoints.size(); j += 2) {
				if (determinant(wallPoints[j + 1] - wallPoints[j], wallPoints[j + 1] - charges[i].getPosition()) *
				        determinant(wallPoints[j + 1] - wallPoints[j], wallPoints[j + 1] - previousPosition) <
				    0) {
					sf::Vector2f v = wallPoints[j + 1] - wallPoints[j];
					sf::Vector2f n = sf::Vector2f(-v.y, v.x);
					n /= Norm(n);
					charges[i].updatePosition(-dt);
					float j = -(1 + 0.5) * dotProduct(charges[i].getSpeed(), n);
					charges[i].setSpeed(charges[i].getSpeed() + j * n);
				}
			}
		}
		// cout<<Charge::getV(mousePos,charges)<<endl ;
		window.clear(sf::Color::White);  ///////////////////// DRAW /////////////////////////
		float quality = VQualitySlider.getSliderValue();
		if (quality != 0) {
			for (int x(0); x < SCR_WIDTH - MENU_WIDTH; x += quality) {
				for (int y(0); y < SCR_HEIGHT; y += quality) {
					float V = Charge::getV(sf::Vector2f(x + MENU_WIDTH, y), charges) * 10;
					for (int i(0); i < quality; i++) {
						for (int j(0); j < quality; j++) {
							image.setPixel(x + i, y + j, sf::Color::Color(0, clamp(255 / 4 * (V + 2), 0, 225), 0));
						}
					}
				}
			}
			texture.loadFromImage(image);
			sprite.setTexture(texture, true);
			window.draw(sprite);
		}

		if (EFieldButton.getCondition()) {
			float d = SCR_HEIGHT / E_FIELD_NUMBER;
			for (int x(0); x < E_FIELD_NUMBER + 1; x++) {
				for (int y(0); y < E_FIELD_NUMBER + 1; y++) {
					sf::Vertex v1(sf::Vector2f(MENU_WIDTH + d * x, d * y));
					v1.color = sf::Color::White;
					sf::Vertex v2(sf::Vector2f(MENU_WIDTH + d * x, d * y) +
					              Charge::getEField(sf::Vector2f(MENU_WIDTH + d * x, d * y), charges, 1000));
					v2.color = sf::Color::White;
					EFieldVA.append(v1);
					EFieldVA.append(v2);
				}
			}
			window.draw(EFieldVA);
		}

		for (int i(0); i < charges.size(); i++) {
			if (!drawNegativeLinesButton.getCondition() && charges[i].getCharge() > 0) {
				EFieldLinesVA = charges[i].getFieldLineVA(fieldLinesSlider.getSliderValue(), charges, sf::Color::White,
				                                          SGMT_LENGTH, SGMT_NB);
				for (int j(0); j < EFieldLinesVA.size(); j++) {
					window.draw(EFieldLinesVA[j]);
				}
			}
			else if (drawNegativeLinesButton.getCondition()) {
				EFieldLinesVA = charges[i].getFieldLineVA(fieldLinesSlider.getSliderValue(), charges, sf::Color::White,
				                                          SGMT_LENGTH, SGMT_NB);
				for (int j(0); j < EFieldLinesVA.size(); j++) {
					window.draw(EFieldLinesVA[j]);
				}
			}
		}

		/*for(int i(0) ; i < charges.size() ; i++)
		{
		    if(charges[i].getCharge()>0)
		        drawPoint(charges[i].getPosition(),5,window,sf::Color::Red) ;
		    else
		        drawPoint(charges[i].getPosition(),5,window,sf::Color::Blue) ;
		}*/

		window.draw(menuBackground);

		EFieldButton.draw(window);
		movingChargeButton.draw(window);
		drawNegativeLinesButton.draw(window);
		chargeSlider.draw(window);
		massSlider.draw(window);
		fieldLinesSlider.draw(window);
		VQualitySlider.draw(window);

		window.display();

		EFieldVA.clear();
		EFieldLinesVA.clear();

		dt = deltaTime.restart().asSeconds();
	}
}
