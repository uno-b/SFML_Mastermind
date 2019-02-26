#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Awesome SFML");

	while (window.isOpen()) {
		window.clear();

		window.display();
	}

	return EXIT_SUCCESS;
}

