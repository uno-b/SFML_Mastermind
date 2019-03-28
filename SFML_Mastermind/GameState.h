#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include "GamePlayStartMenu.h"

namespace Mastermind
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		virtual void Init();

		virtual void HandleInput();
		virtual void Update(float dt);
		virtual void Draw(float dt);

	private:
		GameDataRef _data;

		GamePlayStartMenu *startMenu;

		sf::Sprite _background;
	};
}