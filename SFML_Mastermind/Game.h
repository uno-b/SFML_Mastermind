#pragma once
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

namespace Mastermind
{
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	typedef std::shared_ptr<GameData> GameDataRef;

	class Game
	{
	public:
		Game(int width, int height, std::string title);

	private:
		const float dt = 1.0 / 30.0f; // 60 times per second
		sf::Clock _clock;

		GameDataRef _data = std::make_shared<GameData>();

		void Run();
	};
}