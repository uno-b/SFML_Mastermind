#include "stdafx.h"
#include "InputManager.h"

namespace Mastermind
{
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button,
		sf::RenderWindow & window)
	{
		if (sf::Mouse::isButtonPressed)
		{
			sf::IntRect playButtonRect(
				object.getPosition().x,
				object.getPosition().y,
				object.getGlobalBounds().width,
				object.getGlobalBounds().height);

			if (playButtonRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}
		return false;
	}

	sf::Vector2i GetMousePosition(sf::RenderWindow &window)
	{
		return sf::Mouse::getPosition(window);
	}
}