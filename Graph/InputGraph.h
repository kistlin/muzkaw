#pragma once

#include "Graph.h"
#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

class InputGraph : public Graph {
public:
	InputGraph(std::string const& _path, sf::RenderWindow* _window, sf::Font const& _font);

	void inputPoints();

	void orderPoints();

	void save();

	void update();

private:
	bool point_click_flag;

	int editable_point;
};
