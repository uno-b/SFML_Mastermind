#include "stdafx.h"
#pragma once

#include <sstream>
#include "SplashState.h"
#include "DEFINITIONS.h"
#include "MainMenuState.h"
#include <iostream>

namespace Mastermind
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{
		_data->assets.LoadTexture("Splash State Background",
			SPLASH_SCENE_BACKGROUND_FILEPATH);
		_data->assets.LoadFont("KG Happy", KGHAPPY_FONT_FILEPATH);
		_data->assets.LoadFont("Wunderland", WUNDERLAND_FONT_FILEPATH);

		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"));

		_text.setFont(_data->assets.GetFont("KG Happy"));
		_text.setString("This game was made\nfor everyone :)");
		_text.setCharacterSize(60);
		_text.setFillColor(sf::Color(255, 255, 255, 0));
		_text.setOrigin(_text.getGlobalBounds().width / 2,
			_text.getGlobalBounds().height / 2);
		_text.setPosition(_data->window.getSize().x / 2,
			_data->window.getSize().y / 2);

	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			_data->machine.AddState(StateRef(new MainMenuState(_data)), true);

			std::cout << "Go to main menu state." << std::endl;
		}

		if (!disappear)
		{
			if (textAppearanceTime < 255)
			{
				textAppearanceTime += TEXT_APPEARANCE_TIME * dt;

				_text.setFillColor(sf::Color(255, 255, 255, textAppearanceTime));
			}
			else if (textAppearanceTime == 255 && _clock.getElapsedTime().asSeconds() > 5)
			{
				disappear = true;
			}
		}
		else
		{
			if (textAppearanceTime > 0)
			{
				textAppearanceTime -= TEXT_APPEARANCE_TIME * dt;

				_text.setFillColor(sf::Color(255, 255, 255, textAppearanceTime));
			}
		}
	}

	void SplashState::Draw(float dt)
	{
		_data->window.clear();

		_data->window.draw(_background);

		_data->window.draw(_text);

		_data->window.display();
	}
}