#include "MainMenuState.h"
#include <iostream>
#include <Bengine/ResourceManager.h>
#include <SDL2\SDL.h>
#include "MainMenuGameState.h"
#include "TylerMenuState.h"
MainMenuState::MainMenuState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{

}

void MainMenuState::Entered() {
    std::cout << "IntroGameState has been entered" << std::endl;
	_time = 0.0f;
	rects = new glm::vec4[7];
	for (int i = 0; i < 7; i++)
	{
		rects[i] = glm::vec4(1000,720 - (i + 1) * 45 * 2, 200, 50);
	}
	_hover = 7;
	
					
}

void MainMenuState::Exiting() {
    std::cout << "IntroGameState is exiting" << std::endl;
}

void MainMenuState::Update(float elapsedTime, Bengine::InputManager& inputManager) {
	_time += elapsedTime/400;
	checkCollision(inputManager);
}

void MainMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	Bengine::Color hoverColor;
	hoverColor.r = (sin(_time * 1) + 1)/2 * 255;
    hoverColor.g = (sin(_time * 2) + 1)/2 * 255;
    hoverColor.b = (sin(_time * 3) + 1)/2 * 255;
    hoverColor.a = 255;

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture singlePlayer = Bengine::ResourceManager::getTexture("Textures/MainMenu/singlePlayerText.png");
	static Bengine::GLTexture multiplayer = Bengine::ResourceManager::getTexture("Textures/MainMenu/multiplayerText.png");
	static Bengine::GLTexture mapEditor = Bengine::ResourceManager::getTexture("Textures/MainMenu/mapEditorText.png");
	static Bengine::GLTexture tutorial = Bengine::ResourceManager::getTexture("Textures/MainMenu/tutorialText.png");
	static Bengine::GLTexture settings = Bengine::ResourceManager::getTexture("Textures/MainMenu/settingsText.png");
	static Bengine::GLTexture extras = Bengine::ResourceManager::getTexture("Textures/MainMenu/extrasText.png");
	static Bengine::GLTexture exit = Bengine::ResourceManager::getTexture("Textures/MainMenu/exitText.png");

	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	glm::vec4 rectangle = glm::vec4(640,360,1280,720);
	if(_hover == 0)
		spriteBatch.draw(rects[0],0,uv,singlePlayer.id,0,hoverColor);
	else
		spriteBatch.draw(rects[0],0,uv,singlePlayer.id,0,color);
	if(_hover == 1)
		spriteBatch.draw(rects[1],0,uv,multiplayer.id,0,hoverColor);
	else
		spriteBatch.draw(rects[1],0,uv,multiplayer.id,0,color);
	if(_hover == 2)
		spriteBatch.draw(rects[2],0,uv,mapEditor.id,0,hoverColor);
	else
		spriteBatch.draw(rects[2],0,uv,mapEditor.id,0,color);
	if(_hover == 3)
		spriteBatch.draw(rects[3],0,uv,tutorial.id,0,hoverColor);
	else
		spriteBatch.draw(rects[3],0,uv,tutorial.id,0,color);
	if(_hover == 4)
		spriteBatch.draw(rects[4],0,uv,settings.id,0,hoverColor);
	else
		spriteBatch.draw(rects[4],0,uv,settings.id,0,color);
	if(_hover == 5)
		spriteBatch.draw(rects[5],0,uv,extras.id,0,hoverColor);
	else
		spriteBatch.draw(rects[5],0,uv,extras.id,0,color);
	if(_hover == 6)
		spriteBatch.draw(rects[6],0,uv,exit.id,0,hoverColor);
	else
		spriteBatch.draw(rects[6],0,uv,exit.id,0,color);
	_hover = 7;
}

void MainMenuState::checkCollision(Bengine::InputManager inputManager){
	for (int i = 0; i < 7; i++)
	{
		if(inputManager.getMouseCoords().x < rects[i].x + 100 &&  inputManager.getMouseCoords().x > rects[i].x - 100 && 720 - inputManager.getMouseCoords().y < rects[i].y + 25 && 720 - inputManager.getMouseCoords().y > rects[i].y - 25 )
		{
			if (inputManager.isKeyPressed(SDL_BUTTON_LEFT))
			{
				switch (i)
				{
				case 0 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 1 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 2 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 3 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 4 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 5 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				case 6 :
					this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
					return;
					break;
				}
			}
			_hover = i;
		}
	}
}