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
		_data->assets.LoadTexture("Red", RED);
		_data->assets.LoadTexture("Green", GREEN);
		_data->assets.LoadTexture("Blue", BLUE);
		_data->assets.LoadTexture("Yellow", YELLOW);

		_data->assets.LoadTexture("Red Pin", RED_PIN);
		_data->assets.LoadTexture("White Pin", WHITE_PIN);
		_data->assets.LoadTexture("No Pin", NO_PIN);

		_background.setTexture(_data->assets.GetTexture("Game Background"));
		_red.setTexture(_data->assets.GetTexture("Red"));
		_green.setTexture(_data->assets.GetTexture("Green"));
		_blue.setTexture(_data->assets.GetTexture("Blue"));
		_yellow.setTexture(_data->assets.GetTexture("Yellow"));

		// Color buttons' positions are hard-coded and thus not responsive to the window
		_red.setPosition(sf::Vector2f(482, 460));
		_green.setPosition(sf::Vector2f(553, 460));
		_blue.setPosition(sf::Vector2f(620, 460));
		_yellow.setPosition(sf::Vector2f(690, 460));

		// Pins -//-
		//_redPin
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
			if (event.type == sf::Event::MouseButtonReleased) {
				if (_data->input.IsSpriteClicked(_red, sf::Mouse::Left, _data->window))
				{
					if (flag) {
						PassCode(1);
					}
					else {
						SelectBall(1);
					}
				}
				else if (_data->input.IsSpriteClicked(_green, sf::Mouse::Left, _data->window))
				{
					if (flag) {
						PassCode(2);
					}
					else {
						SelectBall(2);
					}
				}
				else if (_data->input.IsSpriteClicked(_blue, sf::Mouse::Left, _data->window))
				{
					if (flag) {
						PassCode(3);
					}
					else {
						SelectBall(3);
					}
				}
				else if (_data->input.IsSpriteClicked(_yellow, sf::Mouse::Left, _data->window))
				{
					if (flag) {
						PassCode(4);
					}
					else {
						SelectBall(4);
					}
				}
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
		_data->window.draw(_red);
		_data->window.draw(_green);
		_data->window.draw(_blue);
		_data->window.draw(_yellow);

		DrawBalls();
		DrawPins();

		_data->window.display();
	}

	// Logic
	int codeArr[4] = {0, 0, 0, 0};
	sf::Sprite codeArr1[4];
	// Table
	int table[8][4] = { {0, 0, 0, 0},
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 },
					{ 0, 0, 0, 0 } };
	sf::Sprite table1[8][4];
	int currCode = 0;
	//Pins
	int pins[8][4] = { { 3, 3, 3, 3 },
					{ 3, 3, 3, 3 },
					{ 3, 3, 3, 3 },
					{ 3, 3, 3, 3 },
					{ 3, 3, 3, 3 },
					{ 3, 3, 3, 3 },
					{ 3, 3, 3, 3 },
					{ 3, 3, 3, 3 } };
	sf::Sprite pins1[8][4];
	void GameState::PassCode(int code) {
		codeArr[currCode] = code;
		currCode++;

		if (currCode == 4) {
			flag = false;
		}

		CreateSprites();
	}

	void GameState::SelectBall(int code) {
		if (table[currRow][currCol] == 0) {
			table[currRow][currCol] = code;
		}

		if (currCol == 3) {
			CheckPins();

			if (CheckWin()) {
				Reveal();
			}

			currRow++;
			currCol = 0;
		}
		else {
			currCol++;
		}

		CreateSprites();

		CreatePinSprites();
	}

	// Prints out the array for testing
	void GameState::CreateSprites() {
		if (flag) {
			for (int i = 0; i < 4; i++) {
				if (codeArr[i] != 0) {
					switch (codeArr[i]) {
					case 1: codeArr1[i].setTexture(_data->assets.GetTexture("Red"));
						break;
					case 2: codeArr1[i].setTexture(_data->assets.GetTexture("Green"));
						break;
					case 3: codeArr1[i].setTexture(_data->assets.GetTexture("Blue"));
						break;
					case 4: codeArr1[i].setTexture(_data->assets.GetTexture("Yellow"));
						break;
					}
					codeArr1[i].setPosition(sf::Vector2f(480 + (70 * i), 170));
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 4; j++) {
					if (table[i][j] != 0) {
						switch (table[i][j]) {
						case 1: table1[i][j].setTexture(_data->assets.GetTexture("Red"));
							break;
						case 2: table1[i][j].setTexture(_data->assets.GetTexture("Green"));
							break;
						case 3: table1[i][j].setTexture(_data->assets.GetTexture("Blue"));
							break;
						case 4: table1[i][j].setTexture(_data->assets.GetTexture("Yellow"));
							break;
						}
						table1[i][j].setPosition(sf::Vector2f(70 + (80 * j), 470 - (60 * i)));
						//std::cout << table[i][j] << " ";
					}
				}
				//std::cout << std::endl;
			}
		}
	}

	void GameState::CheckPins() {
		int countMatch = 0;
		for (int i = 0; i < 4; i++) {
			if (table[currRow][i] == codeArr[i]) {
				pins[currRow][i] = 1;
			}
			else {
				for (int j = 0; j < 4; j++) {
					if (table[currRow][i] == codeArr[j]) {
						countMatch++;
						break;
					}
				}
			}
		}

		std::cout << countMatch << std::endl;

		for (int i = 0; i < 4; i++) {
			if ((countMatch) != 0 && pins[currRow][i] == 3) {
				pins[currRow][i] = 2;
				countMatch--;
			}
		}
	}

	void GameState::CreatePinSprites() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				if (pins[i][j] != 0) {
					switch (pins[i][j]) {
					case 1: pins1[i][j].setTexture(_data->assets.GetTexture("Red Pin"));
						break;
					case 2: pins1[i][j].setTexture(_data->assets.GetTexture("White Pin"));
						break;
					case 3: pins1[i][j].setTexture(_data->assets.GetTexture("No Pin"));
						break;
					}
					if (j >= 2) {
						pins1[i][j].setPosition(sf::Vector2f(340 + (20 * j), 500 - (59 * i)));
					}
					else {
						pins1[i][j].setPosition(sf::Vector2f(380 + (20 * j), 480 - (59 * i)));
					}
					std::cout << pins[i][j] << " ";
				}
			}
			std::cout << std::endl;
		}
	}

	// Draw new balls
	void GameState::DrawBalls() {
		if (flag) {
			for (int i = 0; i < 4; i++) {
				if (codeArr[i] != 0) {
					_data->window.draw(codeArr1[i]);
				}
			}
		}
		else {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 4; j++) {
					if (table[i][j] != 0) {
						_data->window.draw(table1[i][j]);
					}
				}
			}
		}
	}

	// Draw the pins after every 4 balls
	void GameState::DrawPins() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 4; j++) {
				_data->window.draw(pins1[i][j]);
			}
		}
	}

	// Reset everything when game is over or won
	void GameState::Reveal() {
		flag = true;
	}

	bool GameState::CheckWin() {
		for (int i = 0; i < 4; i++) {
			if (pins[currRow][i] != 1) {
				return false;
			}
		}
		return true;
	}
}