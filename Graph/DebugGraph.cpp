#include "DebugGraph.h"

DebugGraph::DebugGraph(std::string const& _path, float* _x, float* _y, sf::RenderWindow* _window, sf::Font const& _font)
    : Graph(_path, _window, _font) {
	x = _x;
	y = _y;
}

void DebugGraph::update() {
	points.push_back(sf::Vector2f(*x, *y));

	curve.clear();
	for (int i(0); i < points.size(); i++)
		curve.append(sf::Vertex(graphToScreen(points[i]), sf::Color::Blue));
	draw();
}

void DebugGraph::autoscroll() {
	if (points.size() > 1)
		zero_pos.x += graphToScreen(points[points.size() - 2]).x - graphToScreen(points[points.size() - 1]).x;
}

void DebugGraph::draw() {
	window->clear(sf::Color::White);

	drawGrid();
	drawReticle();
	drawAxes();
	drawTicks();
	// drawPoints() ;
	window->draw(curve);

	window->display();
}