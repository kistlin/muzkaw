#include "OutputGraph.h"

OutputGraph::OutputGraph(std::string const& _path, sf::RenderWindow* _window, sf::Font const& _font)
    : Graph(_path, _window, _font) {
	computePolynoms();
	computeCurve();
}

void OutputGraph::drawReticle(sf::Vector2f const& pos) {
	sf::Color color(120, 120, 120);

	sf::VertexArray reticle_x(sf::Lines, 2);
	sf::VertexArray reticle_y(sf::Lines, 2);

	reticle_x[0] = sf::Vertex(sf::Vector2f(0, pos.y), color);
	reticle_x[1] = sf::Vertex(sf::Vector2f(size.x, pos.y), color);

	reticle_y[0] = sf::Vertex(sf::Vector2f(pos.x, 0), color);
	reticle_y[1] = sf::Vertex(sf::Vector2f(pos.x, size.y), color);

	window->draw(reticle_x);
	window->draw(reticle_y);

	std::ostringstream mouse_x;
	std::ostringstream mouse_y;
	mouse_x << screenToGraph(pos).x;
	mouse_y << screenToGraph(pos).y;

	buffer_txt.setColor(sf::Color::Blue);
	buffer_txt.setString(mouse_x.str());
	buffer_txt.setPosition(sf::Vector2f(pos.x, zero_pos.y - tick_size - 10));
	window->draw(buffer_txt);
	buffer_txt.setString(mouse_y.str());
	buffer_txt.setPosition(sf::Vector2f(zero_pos.x + tick_size, pos.y));
	window->draw(buffer_txt);
}
void OutputGraph::draw() {
	window->clear(sf::Color::White);

	drawGrid();
	drawReticle(graphToScreen(sf::Vector2f(x, y)));
	drawAxes();
	drawTicks();
	drawTangents();
	drawPoints();
	window->draw(curve);

	window->display();
}

float OutputGraph::getOutput(float const& input) {
	x = input;
	y = 0;
	for (int i(0); i < curve.getVertexCount() - 1; i++)
		if (screenToGraph(curve[i].position).x < input && input < screenToGraph(curve[i + 1].position).x)
			y = screenToGraph(curve[i].position).y +
			    (input - screenToGraph(curve[i].position).x) *
			        (screenToGraph(curve[i + 1].position).y - screenToGraph(curve[i].position).y) /
			        (screenToGraph(curve[i + 1].position).x - screenToGraph(curve[i].position).x);

	return y;
}

void OutputGraph::update(float const& input) {
	getOutput(input);
	draw();
}
