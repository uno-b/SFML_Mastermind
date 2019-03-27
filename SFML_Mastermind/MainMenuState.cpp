#include "stdafx.h"
#include <sstream>
#include "MainMenuState.h"
//#include "GameState.h"
#include "DEFINITIONS.h"

#include <iostream>

namespace Mastermind
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		_data->assets.LoadTexture("Main Menu State Background",
			MAIN_MENU_BACKGROUND_FILEPATH);
		_data->assets.LoadTexture("Title", GAME_TITLE_FILEPATH);
		_data->assets.LoadTexture("Play Button", PLAY_BUTTON_FILEPATH);
		_data->assets.LoadTexture("Quit Button", QUIT_BUTTON_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Main Menu State Background"));
		_title.setTexture(this->_data->assets.GetTexture("Title"));
		_playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
		_quitButton.setTexture(this->_data->assets.GetTexture("Quit Button"));

		_playButton.setPosition(sf::Vector2f(50, 250));
		_quitButton.setPosition(sf::Vector2f(50, 350));
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}

			if (_data->input.IsSpriteClicked(
				_playButton, sf::Mouse::Left, _data->window))
			{
				//_data->machine.AddState(StateRef(new GameState(_data)),
				//	true);

				std::cout << "Go to game state." << std::endl;
			}

			if (_data->input.IsSpriteClicked(
				_quitButton, sf::Mouse::Left, _data->window))
			{
				_data->window.close();
			}
		}
	}

	void MainMenuState::Update(float dt)
	{

	}

	void MainMenuState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);
		_data->window.draw(_title);
		_data->window.draw(_playButton);
		_data->window.draw(_quitButton);

		_data->window.display();
	}
}