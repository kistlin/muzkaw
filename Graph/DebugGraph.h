#pragma once

#include "Graph.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

class DebugGraph : public Graph {
public:
	DebugGraph(std::string const& _path, float* _x, float* _y, sf::RenderWindow* _window, sf::Font const& _font);
	void autoscroll();
	void update();
	void draw();

private:
	float* x;
	float* y;
};
