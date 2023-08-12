#include "Graph.h"

#include <cmath>

Graph::Graph() {
}

Graph::Graph(std::string const& _path, sf::RenderWindow* _window, sf::Font const& _font) {
	path = _path;

	data = readCfgFile(path);

	font = _font;
	buffer_txt.setCharacterSize(10);
	buffer_txt.setColor(sf::Color::Black);
	buffer_txt.setFont(font);

	title = data[0];
	x_label = data[1];
	y_label = data[2];

	zero_pos = sf::Vector2f(stof(data[3]), stof(data[4]));
	range = sf::Vector2f(stof(data[5]), stof(data[6]));
	size = sf::Vector2f(stof(data[7]), stof(data[8]));
	ticks_spacing = sf::Vector2f(stof(data[9]), stof(data[10]));
	tick_size = stof(data[11]);

	grid_detail = stoi(data[12]);

	point_size = stof(data[13]);

	window = _window;
	window->create(sf::VideoMode(size.x, size.y, 32), title);

	sample_nb = stoi(data[14]);
	curve.setPrimitiveType(sf::LinesStrip);

	mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
	previous_mouse_pos = mouse_pos;

	for (int i(15); i < 15 + (data.size() - 14) / 2; i += 2)
		points.push_back(sf::Vector2f(stof(data[i]), stof(data[i + 1])));

	for (int i(15 + (data.size() - 14) / 2); i < data.size(); i += 2)
		tangents.push_back(sf::Vector2f(stof(data[i]), stof(data[i + 1])));
}

sf::Vector2f Graph::graphToScreen(sf::Vector2f const& v) {
	return sf::Vector2f(v.x * size.x / range.x + zero_pos.x, -v.y * size.y / range.y + zero_pos.y);
}
sf::Vector2f Graph::screenToGraph(sf::Vector2f const& v) {
	return sf::Vector2f((v.x - zero_pos.x) / size.x * range.x, (-v.y + zero_pos.y) / size.y * range.y);
}

void Graph::scroll_zoom() {
	previous_mouse_pos = mouse_pos;
	mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		zero_pos += mouse_pos - previous_mouse_pos;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		range -= 0.01f * (sf::Vector2f((mouse_pos.x - previous_mouse_pos.x) * range.x,
		                               -(mouse_pos.y - previous_mouse_pos.y) * range.y));
		if (range.x <= 0)
			range.x = 0.01;
		if (range.y <= 0)
			range.y = 0.01;
	}
}

void Graph::drawAxes() {
	sf::VertexArray line_x(sf::Lines, 2);
	sf::VertexArray line_y(sf::Lines, 2);

	line_x[0] = sf::Vertex(sf::Vector2f(0, zero_pos.y), sf::Color::Black);
	line_x[1] = sf::Vertex(sf::Vector2f(size.x, zero_pos.y), sf::Color::Black);

	line_y[0] = sf::Vertex(sf::Vector2f(zero_pos.x, 0), sf::Color::Black);
	line_y[1] = sf::Vertex(sf::Vector2f(zero_pos.x, size.y), sf::Color::Black);

	window->draw(line_x);
	window->draw(line_y);

	buffer_txt.setColor(sf::Color::Black);
	buffer_txt.setString(title);
	buffer_txt.setPosition(sf::Vector2f(5, 5));
	window->draw(buffer_txt);
	buffer_txt.setString(x_label);
	buffer_txt.setPosition(sf::Vector2f(size.x - 5 - buffer_txt.getLocalBounds().width, zero_pos.y + tick_size));
	window->draw(buffer_txt);
	buffer_txt.setString(y_label);
	buffer_txt.setPosition(sf::Vector2f(zero_pos.x + 5, 0));
	window->draw(buffer_txt);
}
void Graph::drawTicks() {
	sf::VertexArray ticks_x(sf::Lines, 2 * range.x / ticks_spacing.x + 2);
	sf::VertexArray ticks_y(sf::Lines, 2 * range.y / ticks_spacing.y + 2);

	for (int i(0); i < range.x / ticks_spacing.x; i++) {
		ticks_x[2 * i] = sf::Vertex(
		    sf::Vector2f(rest(zero_pos.x, ticks_spacing.x * size.x / range.x) + i * ticks_spacing.x * size.x / range.x,
		                 zero_pos.y - tick_size),
		    sf::Color::Black);
		ticks_x[2 * i + 1] = sf::Vertex(ticks_x[2 * i].position + sf::Vector2f(0, 2 * tick_size), sf::Color::Black);
	}
	for (int i(0); i < range.y / ticks_spacing.y; i++) {
		ticks_y[2 * i] =
		    sf::Vertex(sf::Vector2f(zero_pos.x - tick_size, rest(zero_pos.y, ticks_spacing.y * size.y / range.y) +
		                                                        i * ticks_spacing.y * size.y / range.y),
		               sf::Color::Black);
		ticks_y[2 * i + 1] = sf::Vertex(ticks_y[2 * i].position + sf::Vector2f(2 * tick_size, 0), sf::Color::Black);
	}

	window->draw(ticks_x);
	window->draw(ticks_y);

	buffer_txt.setColor(sf::Color::Black);
	buffer_txt.setString(data[9]);
	buffer_txt.setPosition(sf::Vector2f(zero_pos.x + ticks_spacing.x * size.x / range.x - 3, zero_pos.y + tick_size));
	window->draw(buffer_txt);
	buffer_txt.setString(data[10]);
	buffer_txt.setPosition(
	    sf::Vector2f(zero_pos.x - tick_size - 15, zero_pos.y - ticks_spacing.y * size.y / range.y - 5));
	window->draw(buffer_txt);
}
void Graph::drawGrid() {
	sf::Color color(220, 220, 220);

	sf::VertexArray grid_x(sf::Lines, 2 * grid_detail * (range.y / ticks_spacing.y + 1) + 2);
	sf::VertexArray grid_y(sf::Lines, 2 * grid_detail * (range.x / ticks_spacing.x + 1) + 2);

	for (int i(0); i < grid_detail * (range.y / ticks_spacing.y + 1); i++) {
		grid_x[2 * i] =
		    sf::Vertex(sf::Vector2f(0, rest(zero_pos.y, ticks_spacing.y * size.y / range.y) +
		                                   (i - grid_detail) * ticks_spacing.y * size.y / range.y / (float)grid_detail),
		               color);
		grid_x[2 * i + 1] = sf::Vertex(grid_x[2 * i].position + sf::Vector2f(size.x, 0), color);
	}
	for (int i(0); i < grid_detail * (range.x / ticks_spacing.x + 1); i++) {
		grid_y[2 * i] =
		    sf::Vertex(sf::Vector2f(rest(zero_pos.x, ticks_spacing.x * size.x / range.x) +
		                                (i - grid_detail) * ticks_spacing.x * size.x / range.x / (float)grid_detail,
		                            0),
		               color);
		grid_y[2 * i + 1] = sf::Vertex(grid_y[2 * i].position + sf::Vector2f(0, size.y), color);
	}

	window->draw(grid_x);
	window->draw(grid_y);
}
void Graph::drawPoints() {
	sf::VertexArray point(sf::Lines, 4);

	sf::Color color = sf::Color::Red;
	point[0].color = color;
	point[1].color = color;
	point[2].color = color;
	point[3].color = color;

	for (int i(0); i < points.size(); i++) {
		point[0].position = graphToScreen(points[i]) + sf::Vector2f(point_size, point_size);
		point[1].position = graphToScreen(points[i]) + sf::Vector2f(-point_size, -point_size);
		point[2].position = graphToScreen(points[i]) + sf::Vector2f(-point_size, point_size);
		point[3].position = graphToScreen(points[i]) + sf::Vector2f(point_size, -point_size);

		window->draw(point);
	}
}
void Graph::drawTangents() {
	sf::VertexArray tangent(sf::Lines, 2);

	sf::Color color = sf::Color::Green;
	tangent[0].color = color;
	tangent[1].color = color;

	for (int i(0); i < points.size(); i++) {
		tangent[0].position = graphToScreen(points[i] + tangents[i]);
		tangent[1].position = graphToScreen(points[i] - tangents[i]);

		window->draw(tangent);
	}
}
void Graph::drawReticle() {
	sf::Color color(120, 120, 120);

	mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	sf::VertexArray reticle_x(sf::Lines, 2);
	sf::VertexArray reticle_y(sf::Lines, 2);

	reticle_x[0] = sf::Vertex(sf::Vector2f(0, mouse_pos.y), color);
	reticle_x[1] = sf::Vertex(sf::Vector2f(size.x, mouse_pos.y), color);

	reticle_y[0] = sf::Vertex(sf::Vector2f(mouse_pos.x, 0), color);
	reticle_y[1] = sf::Vertex(sf::Vector2f(mouse_pos.x, size.y), color);

	window->draw(reticle_x);
	window->draw(reticle_y);

	std::ostringstream mouse_x;
	std::ostringstream mouse_y;
	mouse_x << screenToGraph(mouse_pos).x;
	mouse_y << screenToGraph(mouse_pos).y;

	buffer_txt.setColor(sf::Color::Blue);
	buffer_txt.setString(mouse_x.str());
	buffer_txt.setPosition(sf::Vector2f(mouse_pos.x, zero_pos.y - tick_size - 10));
	window->draw(buffer_txt);
	buffer_txt.setString(mouse_y.str());
	buffer_txt.setPosition(sf::Vector2f(zero_pos.x + tick_size, mouse_pos.y));
	window->draw(buffer_txt);
}

void Graph::computePolynoms() {
	if (points.size() >= 2) {
		polynoms.clear();

		polynoms.resize(points.size() - 1);
		for (int i(0); i < polynoms.size(); i++)
			polynoms[i].resize(4);

		float x1, x2, y1, y2, t1, t2;
		for (int i(0); i < polynoms.size(); i++) {
			x1 = points[i].x;
			x2 = points[i + 1].x;
			y1 = points[i].y;
			y2 = points[i + 1].y;
			t1 = tangents[i].y / tangents[i].x;
			t2 = tangents[i + 1].y / tangents[i + 1].x;

			polynoms[i][0] =
			    -(pow(x1, 3) * x2 * t2 - pow(x1, 3) * y2 - pow(x1, 2) * pow(x2, 2) * t2 + 3 * x2 * y2 * pow(x1, 2) +
			      pow(x1, 2) * pow(x2, 2) * t1 - 3 * pow(x2, 2) * y1 * x1 - x1 * pow(x2, 3) * t1 + pow(x2, 3) * y1) /
			    (pow(x1, 3) - 3 * x2 * pow(x1, 2) - pow(x2, 3) + 3 * x1 * pow(x2, 2));

			polynoms[i][1] = (pow(x1, 3) * t2 + 2 * pow(x1, 2) * x2 * t1 + pow(x1, 2) * x2 * t2 + 6 * x1 * x2 * y2 -
			                  2 * pow(x2, 2) * x1 * t2 - 6 * x1 * x2 * y1 - pow(x2, 2) * x1 * t1 - pow(x2, 3) * t1) /
			                 (pow(x1, 3) - 3 * x2 * pow(x1, 2) - pow(x2, 3) + 3 * x1 * pow(x2, 2));

			polynoms[i][2] = -(2 * pow(x1, 2) * t2 + pow(x1, 2) * t1 - 3 * x1 * y1 - x1 * x2 * t2 + 3 * x1 * y2 +
			                   x1 * x2 * t1 - 2 * pow(x2, 2) * t1 - 3 * x2 * y1 - pow(x2, 2) * t2 + 3 * x2 * y2) /
			                 ((-x2 + x1) * (pow(x1, 2) - 2 * x2 * x1 + pow(x2, 2)));

			polynoms[i][3] = (-2 * y1 + x1 * t2 + x1 * t1 - x2 * t2 - x2 * t1 + 2 * y2) /
			                 (pow(x1, 3) - 3 * x2 * pow(x1, 2) - pow(x2, 3) + 3 * x1 * pow(x2, 2));
		}
	}
}
void Graph::computeCurve() {
	curve.clear();

	if (points.size() >= 2) {
		for (int i(0); i < sample_nb; i++) {
			for (int j(0); j < points.size() - 1; j++) {
				float x = screenToGraph(sf::Vector2f(i * size.x / (float)sample_nb, 0)).x;

				if (x > points[j].x && x <= points[j + 1].x) {
					curve.append(sf::Vertex(
					    graphToScreen(sf::Vector2f(x, polynoms[j][0] + polynoms[j][1] * x + polynoms[j][2] * pow(x, 2) +
					                                      polynoms[j][3] * pow(x, 3))),
					    sf::Color::Blue));
				}
			}
		}
	}
}

void Graph::draw() {
	window->clear(sf::Color::White);

	drawGrid();
	drawReticle();
	drawAxes();
	drawTicks();
	drawTangents();
	drawPoints();
	window->draw(curve);

	window->display();
}
