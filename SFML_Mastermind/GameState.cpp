#include "stdafx.h"
#include <sstream>
#include "GameState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"

#include <iostream>

namespace Mastermind
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
		_data->window.setFramerateLimit(30);
	}

	void GameState::Init()
	{

		_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);

		_background.setTexture(_data->assets.GetTexture("Game Background"));

		startMenu = new GamePlayStartMenu(_data);
	}

	void GameState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(startMenu->GetGrammarSprite(),
				sf::Mouse::Left, _data->window))
			{
				_data->machine.AddState(StateRef(new GrammarState(_data)), true);
			}

			if (_data->input.IsSpriteClicked(startMenu->GetVocabularySprite(),
				sf::Mouse::Left, _data->window))
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(startMenu->GetOlympiadSprite(),
				sf::Mouse::Left, _data->window))
			{
				_data->window.close();
			}
		}
	}

	void GameState::Update(float dt)
	{

	}

	void GameState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);

		startMenu->Draw();

		_data->window.display();
	}
}