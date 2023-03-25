#pragma once

#include "Point.h"
#include "Utility.h"

class Charge : public Point {
public:
	Charge(float charge, float mass, sf::Vector2f const& position);
	float getCharge() const;
	void setCharge(float const& charge);

	sf::Vector2f getCoulombForce(Charge const& e) const;
	std::vector<sf::Vector2f> getFieldLine(sf::Vector2f const& start, float const& angle,
	                                       std::vector<Charge> const& charges, float const& segmentLength,
	                                       int const& segmentNumber) const;
	std::vector<sf::VertexArray> getFieldLineVA(int const& nbOfLines, std::vector<Charge> const& charges,
	                                            sf::Color const& color, float const& segmentLength,
	                                            int const& segmentNumber) const;

	std::vector<sf::Vector2f> getVField(std::vector<Charge> const& charge, float const& segmentLength,
	                                    sf::Vector2f start, int segmentNumber) const;
	std::vector<sf::VertexArray> getVFieldVA(int const& nbOfLines, std::vector<Charge> const& charges,
	                                         sf::Color const& color, float const& segmentLength,
	                                         int const& segmentNumber) const;

	static sf::Vector2f getEField(sf::Vector2f const& M, std::vector<Charge> const& charge, float const& segmentLength);
	static sf::Vector2f getNormalizedEField(sf::Vector2f const& M, std::vector<Charge> const& charge,
	                                        float const& segmentLength);
	static float getV(sf::Vector2f const& M, std::vector<Charge> const& charge);

private:
	float m_charge;
};
