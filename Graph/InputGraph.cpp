#include "InputGraph.h"

InputGraph::InputGraph(std::string const& _path, sf::RenderWindow* _window, sf::Font const& _font)
    : Graph(_path, _window, _font) {
	point_click_flag = false;

	editable_point = -1;
}

void InputGraph::inputPoints() {
	mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		editable_point = -1;

		for (int i(0); i < points.size(); i++)
			if (Distance(graphToScreen(points[i]), mouse_pos) < 10) {
				editable_point = i;
			}
	}

	if (editable_point == -1) {
		if (mouseClickedOnce(sf::Mouse::Left, point_click_flag)) {
			points.push_back(screenToGraph(mouse_pos));
			tangents.push_back(sf::Vector2f(0, 0));
		}
	}

	else {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			points[editable_point] = screenToGraph(mouse_pos);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			tangents[editable_point] = screenToGraph(mouse_pos) - points[editable_point];
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) {
			points.erase(points.begin() + editable_point);
			tangents.erase(tangents.begin() + editable_point);
		}
	}
}

void InputGraph::orderPoints() {
	std::vector<sf::Vector2f> buffer;

	while (points.size() > 0) {
		int min = 0;
		for (int i(0); i < points.size(); i++) {
			if (points[i].x < points[min].x)
				min = i;
		}
		buffer.push_back(points[min]);
		points.erase(points.begin() + min);
	}

	points = buffer;
}

void InputGraph::save() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		std::ofstream cfg(path);
		cfg << "0-title: " << title << "\n \n";
		cfg << "1-x_label: " << x_label << "\n";
		cfg << "2-y_label: " << y_label << "\n \n";
		cfg << "3-x_zero: " << zero_pos.x << "\n";
		cfg << "4-y_zero: " << zero_pos.y << "\n \n";
		cfg << "5-x_range: " << range.x << "\n";
		cfg << "6-y_range: " << range.y << "\n \n";
		cfg << "7-x_size: " << window->getSize().x << "\n";
		cfg << "8-y_size: " << window->getSize().y << "\n \n";
		cfg << "9-x_ticks_spacing: " << ticks_spacing.x << "\n";
		cfg << "10-y_ticks_spacing: " << ticks_spacing.y << "\n \n";
		cfg << "11-tick_size: " << tick_size << "\n \n";
		cfg << "12-grid_detail: " << grid_detail << "\n \n";
		cfg << "13-point_size: " << point_size << "\n \n";
		cfg << "14-sample_number: " << sample_nb << "\n \n \n";

		for (int i(0); i < points.size(); i++) {
			cfg << "point" << i + 1 << "_x: " << points[i].x << "\n";
			cfg << "point" << i + 1 << "_y: " << points[i].y << "\n";
		}
		cfg << "\n \n";
		for (int i(0); i < tangents.size(); i++) {
			cfg << "tangent" << i + 1 << "_x: " << tangents[i].x << "\n";
			cfg << "tangent" << i + 1 << "_y: " << tangents[i].y << "\n";
		}
	}
}

void InputGraph::update() {
	scroll_zoom();
	inputPoints();
	orderPoints();
	computePolynoms();
	computeCurve();
	draw();
	save();
}