#include "RemedyMenuState.h"
#include "MainMenuGameState.h"
#include "MainGame.h"
#include "LevelLoader.h"
#include "Drawable.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include "tinyxml2.h"

using namespace tinyxml2;


#define CAMERA TheMainGame::Instance()->_camera
#define WIDTH 32
#define HEIGHT 18


RemedyMenuState::RemedyMenuState(const std::shared_ptr<GameStateManager> &gameStateManager) :
	gameStateManager(gameStateManager) 
{

}

void RemedyMenuState::Entered()
{
	LevelLoader loader;
	level = loader.LoadLevel();
	mousePressed = false;
	changed = false;
	
}

void RemedyMenuState::Exiting()
{

}

void RemedyMenuState::Update(float elapsedTime, Bengine::InputManager& inputManager)
{
	ProcessInput(inputManager);
}

void RemedyMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{

	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/TestTile.png");
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	for (int i = 0; i < HEIGHT; ++i)
	{
		for (int j = 0; j < WIDTH; ++j)
		{
			if (level[i][j] == 1)
			{
				spriteBatch.draw(glm::vec4(CAMERA.getScreenDimensions().x/WIDTH/2 + j*CAMERA.getScreenDimensions().x/WIDTH,CAMERA.getScreenDimensions().y/HEIGHT/2 + i*CAMERA.getScreenDimensions().y/HEIGHT,CAMERA.getScreenDimensions().x/WIDTH, CAMERA.getScreenDimensions().y/HEIGHT), 0.0f, uv, spook.id, 0.0f, color);
			}
		}
	}
}

void RemedyMenuState::ProcessInput(Bengine::InputManager _inputManager)
{
	if (_inputManager.isKeyPressed(SDLK_BACKSPACE))
	{
		this->gameStateManager->Switch(std::shared_ptr<GameState>(new MainMenuGameState(gameStateManager)));
		return;
	}
	if (_inputManager.isKeyPressed(SDLK_s))
	{
		SaveXML(level);
	}
	if (_inputManager.isKeyPressed(SDLK_SPACE))
	{
		for(int i = 0; i < HEIGHT; ++i)
		{
			for (int j = 0; j < WIDTH; ++j)
			{
				level[i][j] = 0;
			}
		}
	}

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT) || _inputManager.isKeyPressed(SDL_BUTTON_RIGHT))
	{
		if (!mousePressed)
		{
			int** tempArray = new int*[HEIGHT];
			for (int i = 0; i < HEIGHT; ++i)
			{
				tempArray[i] = new int[WIDTH];
			}
			for (int i = 0; i < HEIGHT; ++i)
			{
				for (int j = 0; j < WIDTH; ++j)
				{
					tempArray[i][j] = 0;
				}
			}
			mousePressed = true;
			tileChangedArray = tempArray;
		}

		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords = CAMERA.convertScreenToWorld(mouseCoords);

		tileCoords.x = floor((mouseCoords.x / 40));
		tileCoords.y = floor((mouseCoords.y / 40));

		if (!changed)
		{
			tempX = tileCoords.x;
			tempY = tileCoords.y;
			if (tileChangedArray[(int)tileCoords.y][(int)tileCoords.x] == 0)
			{
				if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
				{
					level[(int)tileCoords.y][(int)tileCoords.x]++;
				}
				else
				{
					level[(int)tileCoords.y][(int)tileCoords.x]--;
					if (level[(int)tileCoords.y][(int)tileCoords.x] < 0)
					{
						level[(int)tileCoords.y][(int)tileCoords.x] += 2; //add number of tiles
					}
				}
				level[(int)tileCoords.y][(int)tileCoords.x] %= 2; //modulus number of tiles
				changed = true;
				tileChangedArray[(int)tileCoords.y][(int)tileCoords.x] = 1;
			}
		}

		if (changed)
		{
			if (tempX != tileCoords.x || tempY != tileCoords.y)
			{
				changed = false;
			}
		}
	}						
	if (!_inputManager.isKeyPressed(SDL_BUTTON_LEFT) && !_inputManager.isKeyPressed(SDL_BUTTON_RIGHT))
	{
		mousePressed = false;
		changed = false;
	}

}

void RemedyMenuState::SaveXML(int** level)
{
	XMLDocument xmlDoc;
	xmlDoc.LoadFile("TestLevel.xml");
	XMLNode * pRoot = xmlDoc.FirstChild();

	XMLElement * rowElement = pRoot->FirstChildElement("Row");
	XMLElement * tileElement;

	int h = 0;
	int w = 0;
	for (rowElement = pRoot->FirstChildElement("Row"); rowElement != NULL; rowElement = rowElement->NextSiblingElement("Row"))
	{
		for(tileElement = rowElement->FirstChildElement("Tile"); tileElement != NULL; tileElement = tileElement->NextSiblingElement("Tile"))
		{
			tileElement->SetText(level[h][w]);
			w++;
		}
		h++;
		w = 0;
	}

	xmlDoc.SaveFile("TestLevel.xml");
	std::cout << "Level Saved!";
	return;

}

