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
	BuildLevel(level);
	ball = new Ball(world, CAMERA.getScreenDimensions().x / 2, CAMERA.getScreenDimensions().y / 2);
	
}

void RemedyMenuState::Exiting()
{

}

void RemedyMenuState::Update(float elapsedTime, Bengine::InputManager& inputManager)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(elapsedTime, velocityIterations, positionIterations);
}

void RemedyMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	for (int i = 0; i < tiles.size(); ++i)
	{
		tiles[i]->Draw(spriteBatch);
	}
	ball->Draw(spriteBatch);
}

void RemedyMenuState::BuildLevel(int** level)
{
	world = new b2World(b2Vec2(-50.0f, -10.0f));
	//create box if tile exists
	for (int i = 0; i < HEIGHT; ++i)
	{	
		for (int j = 0; j < WIDTH; ++j)
		{
			if (level[i][j] != 0)
			{
				tiles.push_back(new PhysicsTile(world, b2Vec2(j * CAMERA.getScreenDimensions().x / WIDTH + CAMERA.getScreenDimensions().x/WIDTH/2, i * CAMERA.getScreenDimensions().y / HEIGHT + CAMERA.getScreenDimensions().y/HEIGHT/2), level[i][j]));
			}
		}
	}
}