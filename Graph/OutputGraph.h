#pragma once

#include "Graph.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

class OutputGraph : public Graph {
public:
	OutputGraph(std::string const& _path, sf::RenderWindow* _window, sf::Font const& _font);

	void drawReticle(sf::Vector2f const& pos);
	void draw();  // draw function with reticle on place

	float getOutput(float const& input);

	void update(float const& input);

private:
	float x;
	float y;
};
