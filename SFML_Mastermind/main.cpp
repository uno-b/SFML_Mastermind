#include "stdafx.h"
#include "DEFINITIONS.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Awesome SFML");

	while (window.isOpen()) {
		window.clear();

		window.display();
	}

	return EXIT_SUCCESS;
}

