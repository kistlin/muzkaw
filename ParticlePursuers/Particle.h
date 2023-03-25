#pragma once

#include <SFML/Graphics.hpp>

class Particle  // class that manages particles following the Newton's law
{
public:
	Particle();
	Particle(float mass, sf::Vector2f position, sf::Color _color);

	float getMass() const;
	void setMass(float const& mass);
	std::vector<sf::Vector2f> getForce() const;
	sf::Vector2f getTotalForce() const;
	void addForce(sf::Vector2f const& force);
	void clearForce();
	sf::Vector2f getPosition() const;
	sf::Vector2f getPreviousPosition() const;
	void setPosition(sf::Vector2f const& position);
	sf::Vector2f getSpeed() const;
	void setSpeed(sf::Vector2f const& speed);
	sf::Vector2f getAcceleration() const;
	void setAcceleration(sf::Vector2f const& acceleration);
	void setStatic();
	void setMovable();
	bool isMovable() const;

	void updatePosition(float const& dt);  // the only important method in this class !

	void draw(sf::RenderWindow& window);

private:
	float m_mass;

	std::vector<sf::Vector2f> m_force;  // forces applied to this particle
	sf::Vector2f m_position;            // position of the particle
	sf::Vector2f m_previousPosition;
	sf::Vector2f
	    m_speed;  // speed of the particle : speed v= ( x(t+dt) - x(t) ) / dt is the finite manner to say v=dx/dt
	sf::Vector2f m_acceleration;  // acceleration of the particle : acceleration a= ( v(t+dt) - v(t) ) / dt is the
	                              // finite manner to say a=dv/dt

	bool m_movable;

	std::vector<sf::Vector3f> tracer;
	sf::VertexArray VA;
	sf::Color color;
};
