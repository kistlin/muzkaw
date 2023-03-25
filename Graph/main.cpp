#include "DebugGraph.h"
#include "Graph.h"
#include "InputGraph.h"
#include "OutputGraph.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <stdlib.h>

int main() {
	sf::RenderWindow window;
	window.setFramerateLimit(30);

	sf::Font arial;
	arial.loadFromFile("arial.ttf");

	std::string path = "cfg.txt";
	// std::cout << "path : ";
	// std::cin >> path;
	InputGraph graph(path, &window, arial);

	sf::Event event;

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
		}
		graph.update();
	}
}
