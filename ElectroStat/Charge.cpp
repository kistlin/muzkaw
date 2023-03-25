#include "Charge.h"
#include <iostream>

Charge::Charge(float charge, float mass, sf::Vector2f const& position) {
	m_charge = charge;
	setMass(mass);
	setPosition(position);
	setMovable();
}

float Charge::getCharge() const {
	return m_charge;
}

void Charge::setCharge(float const& charge) {
	m_charge = charge;
}

sf::Vector2f Charge::getCoulombForce(Charge const& e) const {
	return static_cast<float>(
	           (100000000.f * getCharge() * e.getCharge() / pow(Distance(getPosition(), e.getPosition()), 3))) *
	       (getPosition() - e.getPosition());
}

std::vector<sf::Vector2f> Charge::getFieldLine(sf::Vector2f const& start, float const& angle,
                                               std::vector<Charge> const& charges, float const& segmentLength,
                                               int const& segmentNumber) const {
	sf::Vector2f p = rotatePoint(start + sf::Vector2f(0, -1), start, angle);
	std::vector<sf::Vector2f> E;
	E.push_back(p);

	for (int i(1); i < segmentNumber; i++) {
		E.push_back(E[i - 1] +
		            getCharge() / abs(getCharge()) * Charge::getNormalizedEField(E[i - 1], charges, segmentLength));
	}

	return E;
}

std::vector<sf::VertexArray> Charge::getFieldLineVA(int const& nbOfLines, std::vector<Charge> const& charges,
                                                    sf::Color const& color, float const& segmentLength,
                                                    int const& segmentNumber) const {
	std::vector<sf::VertexArray> EVA(nbOfLines);
	std::vector<std::vector<sf::Vector2f>> E(nbOfLines);
	sf::Vertex v;
	for (int i(0); i < nbOfLines; i++) {
		E[i] = getFieldLine(getPosition(), i * (360 / nbOfLines), charges, segmentLength, segmentNumber);
	}
	for (int i(0); i < nbOfLines; i++) {
		EVA[i].setPrimitiveType(sf::LinesStrip);
		for (int j(0); j < E[i].size(); j++) {
			v.position = sf::Vector2f(E[i][j]);
			v.color = color;
			EVA[i].append(v);
		}
	}
	return EVA;
}

sf::Vector2f Charge::getEField(sf::Vector2f const& M, std::vector<Charge> const& charge, float const& segmentLength) {
	sf::Vector2f result(0, 0);
	for (int i(0); i < charge.size(); i++) {
		result += static_cast<float>(charge[i].getCharge() / pow(Distance(M, charge[i].getPosition()), 2)) *
		          (M - charge[i].getPosition());
	}
	return result * segmentLength;
}

sf::Vector2f Charge::getNormalizedEField(sf::Vector2f const& M, std::vector<Charge> const& charge,
                                         float const& segmentLength) {
	sf::Vector2f result(0, 0);
	for (int i(0); i < charge.size(); i++) {
		result += static_cast<float>(charge[i].getCharge() / pow(Distance(M, charge[i].getPosition()), 2)) *
		          (M - charge[i].getPosition());
	}
	return result / Norm(result) * segmentLength;
}

float Charge::getV(sf::Vector2f const& M, std::vector<Charge> const& charge) {
	float result = 0;
	for (int i(0); i < charge.size(); i++) {
		result += charge[i].getCharge() / Distance(M, charge[i].getPosition());
	}
	return result;
}
