#include "Particle.h"

Particle::Particle() {
	m_mass = 50;
	m_position = sf::Vector2f(50, 50);
	m_speed = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);
	m_movable = true;

	VA.setPrimitiveType(sf::LinesStrip);
}
Particle::Particle(float mass, sf::Vector2f position, sf::Color _color) {
	m_mass = mass;
	m_position = position;
	m_speed = sf::Vector2f(0, 0);
	m_acceleration = sf::Vector2f(0, 0);

	color = _color;
	VA.setPrimitiveType(sf::LinesStrip);
}

float Particle::getMass() const {
	return m_mass;
}
void Particle::setMass(float const& mass) {
	m_mass = mass;
}

std::vector<sf::Vector2f> Particle::getForce() const {
	return m_force;
}
sf::Vector2f Particle::getTotalForce() const {
	sf::Vector2f totalForce(0, 0);
	for (int i(0); i < m_force.size(); i++) {
		totalForce += m_force[i];
	}
	return totalForce;
}
void Particle::addForce(sf::Vector2f const& force) {
	m_force.push_back(force);
}
void Particle::clearForce() {
	m_force.clear();
}

sf::Vector2f Particle::getPosition() const {
	return m_position;
}
sf::Vector2f Particle::getPreviousPosition() const {
	return m_previousPosition;
}
void Particle::setPosition(sf::Vector2f const& position) {
	m_position = position;
}

sf::Vector2f Particle::getSpeed() const {
	return m_speed;
}
void Particle::setSpeed(sf::Vector2f const& speed) {
	m_speed = speed;
}

sf::Vector2f Particle::getAcceleration() const {
	return m_acceleration;
}
void Particle::setAcceleration(sf::Vector2f const& acceleration) {
	m_acceleration = acceleration;
}
void Particle::setStatic() {
	m_movable = false;
}
void Particle::setMovable() {
	m_movable = true;
}
bool Particle::isMovable() const {
	return m_movable;
}

void Particle::updatePosition(float const& dt) {
	m_previousPosition = m_position;  // if x is the position : we store x(t)
	/*
	Newton's law states : F=m*a, that is to say a=F/m
	we integrate this equation with the following approximation : between each frame, the acceleration is constant (it's
	nearly true) Notation : x(t) is the position during the current frame, x(t+dt) is the position we want to find for
	the next frame. Same for v(t)... so we have v(t+dt)=(F/m)*dt + v(t) -> if we differentiate this equation, we indeed
	find back a=F/m we integrate again the equation above considering that v is constant aswell thus we get x(t+dt) =
	(1/2)*(F/m)*dt^2 + v(t)*dt + x(t) -> knowing F, m, dt, the speed of the particle and its position, we can guess its
	next position ! this is known as the leapfrog numerical integration. I think that it is equivalent to the Runge
	Kutta order 2 (RK2)
	*/
	m_position = m_position + m_speed * dt +
	             0.5f * getTotalForce() / m_mass * (float)pow(dt, 2);  // the equation explained above
	m_speed = (m_position - m_previousPosition) /
	          dt;  // now we need to update the speed by differentiating the position. (now we have the new position and
	               // the new speed : the particle moves !)

	tracer.push_back(sf::Vector3f(m_position.x, m_position.y, 100));
	for (int i(0); i < tracer.size(); i++) {
		tracer[i].z = std::max(tracer[i].z - 100 * dt, 0.f);
		if (tracer[i].z == 0)
			tracer.erase(tracer.begin() + i);
	}

	VA.clear();
	for (int i(0); i < tracer.size(); i++)
		VA.append(sf::Vertex(sf::Vector2f(tracer[i].x, tracer[i].y),
		                     sf::Color::Color(color.r, color.g, color.b, tracer[i].z * 2.5)));
}

void Particle::draw(sf::RenderWindow& window) {
	window.draw(VA);
}