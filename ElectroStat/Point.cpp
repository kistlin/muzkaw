#include "Point.h"

Point::Point() {
	m_mass = 50;
	m_position = sf::Vector2f(50, 50);
	m_speed = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_movable = true;
}
Point::Point(float mass, sf::Vector2f position, sf::Vector2f speed) {
	m_mass = mass;
	m_position = position;
	m_speed = speed;
}

float Point::getMass() const {
	return m_mass;
}

void Point::setMass(float const& mass) {
	m_mass = mass;
}

std::vector<sf::Vector2f> Point::getForce() const {
	return m_force;
}

sf::Vector2f Point::getTotalForce() const {
	sf::Vector2f totalForce(0, 0);
	for (int i(0); i < m_force.size(); i++) {
		totalForce += m_force[i];
	}
	return totalForce;
}

void Point::addForce(sf::Vector2f const& force) {
	m_force.push_back(force);
}

void Point::clearForce() {
	m_force.clear();
}

sf::Vector2f Point::getPosition() const {
	return m_position;
}

void Point::setPosition(sf::Vector2f const& position) {
	m_position = position;
}

sf::Vector2f Point::getSpeed() const {
	return m_speed;
}

void Point::setSpeed(sf::Vector2f const& speed) {
	m_speed = speed;
}

sf::Vector2f Point::getAcceleration() const {
	return m_acceleration;
}

void Point::setAcceleration(sf::Vector2f const& acceleration) {
	m_acceleration = acceleration;
}

void Point::setStatic() {
	m_movable = false;
}

void Point::setMovable() {
	m_movable = true;
}

bool Point::isMovable() {
	return m_movable;
}

void Point::updatePosition(float const& dt) {
	sf::Vector2f previousPosition = m_position;
	m_position = m_position + m_speed * dt + 0.5f * getTotalForce() / m_mass * (float)pow(dt, 2);
	m_speed = (m_position - previousPosition) / dt;
}
