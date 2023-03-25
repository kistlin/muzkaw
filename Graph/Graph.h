#pragma once

#include "Utility.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>

class Graph {
public:
	Graph();
	Graph(std::string const& _path, sf::RenderWindow* _window, sf::Font const& _font);

	sf::Vector2f graphToScreen(sf::Vector2f const& v);
	sf::Vector2f screenToGraph(sf::Vector2f const& v);

	void scroll_zoom();

	void drawAxes();
	void drawTicks();
	void drawGrid();
	void drawPoints();
	void drawTangents();
	void drawReticle();

	void computePolynoms();
	void computeCurve();

	void draw();

protected:
	sf::RenderWindow* window;

	std::vector<std::string> data;

	std::string path;

	sf::Font font;
	sf::Text buffer_txt;

	sf::Vector2f zero_pos;
	sf::Vector2f mouse_pos;
	sf::Vector2f previous_mouse_pos;
	sf::Vector2f range;
	sf::Vector2f size;
	sf::Vector2f ticks_spacing;
	float tick_size;
	int grid_detail;

	std::string title;
	std::string x_label;
	std::string y_label;

	std::vector<sf::Vector2f> points;
	std::vector<sf::Vector2f> tangents;
	float point_size;

	std::vector<std::vector<float>> polynoms;
	int sample_nb;
	sf::VertexArray curve;
};
