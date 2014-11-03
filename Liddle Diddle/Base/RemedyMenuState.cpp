#include "RemedyMenuState.h"
#include "MainGame.h"
#include "LevelLoader.h"
#include "Drawable.h"
#include <SDL2/SDL.h>
#include <iostream>

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
	XMLDocument xmlDoc;
	level = loader.LoadLevel();
}

void RemedyMenuState::Exiting()
{

}

void RemedyMenuState::Update(float elapsedTime, Bengine::InputManager& inputManager)
{

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

}

