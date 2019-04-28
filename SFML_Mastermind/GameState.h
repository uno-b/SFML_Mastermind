#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"

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

		// Logic
		void SelectBall(int code);
		void PassCode(int code);
		void CreateSprites();
		void CheckPins();
		void CreatePinSprites();
		void DrawBalls();
		void DrawPins();
		void Reveal();
		bool CheckWin();

	private:
		GameDataRef _data;
		
		sf::Sprite _background;
		sf::Sprite _red;
		sf::Sprite _green;
		sf::Sprite _blue;
		sf::Sprite _yellow;
		sf::Sprite _ball;

		sf::Sprite _redPin;
		sf::Sprite _whitePin;
		sf::Sprite _noPin;

		bool flag = true;
		
		// Row goes from 0-7, col goes from 0-3
		int currRow = 0;
		int currCol = 0;
	};
}