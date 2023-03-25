#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

class Point {
public:
	Point();
	Point(float mass, sf::Vector2f position, sf::Vector2f speed);

	float getMass() const;
	void setMass(float const& mass);
	std::vector<sf::Vector2f> getForce() const;
	sf::Vector2f getTotalForce() const;
	void addForce(sf::Vector2f const& force);
	void clearForce();
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f const& position);
	sf::Vector2f getSpeed() const;
	void setSpeed(sf::Vector2f const& speed);
	sf::Vector2f getAcceleration() const;
	void setAcceleration(sf::Vector2f const& acceleration);
	void setStatic();
	void setMovable();
	bool isMovable();

	void updatePosition(float const& dt);

private:
	float m_mass;

	std::vector<sf::Vector2f> m_force;
	sf::Vector2f m_position;
	sf::Vector2f m_speed;
	sf::Vector2f m_acceleration;

	bool m_movable;
};
