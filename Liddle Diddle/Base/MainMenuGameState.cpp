#include "MainMenuGameState.h"
#include "TylerMenuState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>




MainMenuGameState::MainMenuGameState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void MainMenuGameState::Entered() {
    std::cout << "MainMenuState has been entered" << std::endl;
	_WigiRect = glm::vec4(200,720-150,200,100);
	_MikeRect = glm::vec4(200,150,200,100);
	_KingRect = glm::vec4(1280-200,720-200,300,300);
	_RemedyRect = glm::vec4(1080,150,200,100);
	rotation = 0;
}

void MainMenuGameState::Exiting() {
    std::cout << "MainMenuState is exiting" << std::endl;
}

void MainMenuGameState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {

	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords.y = 720 - mouseCoords.y;

		if (mouseCoords.x < _WigiRect.x + 100 && mouseCoords.x > _WigiRect.x -100 && mouseCoords.y > _WigiRect.y - 50 && mouseCoords.y < _WigiRect.y +50)
		{
			//this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
			std::cout << "Wigi\n"; 
		}
		if (mouseCoords.x < _MikeRect.x + 100 && mouseCoords.x > _MikeRect.x -100 && mouseCoords.y > _MikeRect.y - 50 && mouseCoords.y < _MikeRect.y +50)
		{
			//this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
			std::cout << "Mike\n"; 
		}
		if (mouseCoords.x < _RemedyRect.x + 100 && mouseCoords.x > _RemedyRect.x -100 && mouseCoords.y > _RemedyRect.y - 50 && mouseCoords.y < _RemedyRect.y +50)
		{
			//this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
			std::cout << "Remedy\n"; 
		}
		if (glm::length(glm::vec2(mouseCoords.x,mouseCoords.y) - glm::vec2(_KingRect.x,_KingRect.y)) <= 150)
		{
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new TylerMenuState(gameStateManager)));
		}
	}
 }

void MainMenuGameState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	static Bengine::GLTexture King = Bengine::ResourceManager::getTexture("Textures/King.png");
	static Bengine::GLTexture Mike = Bengine::ResourceManager::getTexture("Textures/Mike.png");
	static Bengine::GLTexture Wigi = Bengine::ResourceManager::getTexture("Textures/Wigi.png");
	static Bengine::GLTexture Remedy = Bengine::ResourceManager::getTexture("Textures/Remedy.png");


	glm::vec4 rectangle = glm::vec4(640,360,1280,720);

	spriteBatch.draw(_KingRect, rotation += 0.01, uv, King.id, 0.0f, color);
	spriteBatch.draw(_MikeRect, 0, uv, Mike.id, 0.0f, color);
	spriteBatch.draw(_WigiRect, 0, uv, Wigi.id, 0.0f, color);
	spriteBatch.draw(_RemedyRect, 0, uv, Remedy.id, 0.0f, color);
}