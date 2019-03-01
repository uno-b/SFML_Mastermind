#pragma once

#include "State.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

namespace Mastermind
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Texture _backgroundTexture;
		sf::Sprite _background;
	};
}