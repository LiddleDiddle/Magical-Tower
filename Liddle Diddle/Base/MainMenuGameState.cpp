#include "MainMenuGameState.h"
#include "RemedyMenuState.h"
#include "TylerMenuState.h"
#include "TilemapEditorState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>
#include "MainGame.h"
#include "StartScreenState.h"



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
	_gameRect = glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x/2,TheMainGame::Instance()->_camera.getScreenDimensions().y/2,300,100);
	rotation = 0;
}

void MainMenuGameState::Exiting() {
    std::cout << "MainMenuState is exiting" << std::endl;
}

void MainMenuGameState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	rotation -= elapsedTime;
	if (_inputManager.isKeyDown(SDL_BUTTON_LEFT)){
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
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new RemedyMenuState(gameStateManager)));
		}

		if (mouseCoords.x < _gameRect.x + 100 && mouseCoords.x > _gameRect.x -100 && mouseCoords.y > _gameRect.y - 50 && mouseCoords.y < _gameRect.y +50)
		{
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new StartScreenState(gameStateManager)));
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
	Bengine::ColorRGBA8 color(255,255,255,255);

	static Bengine::GLTexture King = Bengine::ResourceManager::getTexture("Textures/King.png");
	static Bengine::GLTexture Mike = Bengine::ResourceManager::getTexture("Textures/Mike.png");
	static Bengine::GLTexture Wigi = Bengine::ResourceManager::getTexture("Textures/Wigi.png");
	static Bengine::GLTexture Remedy = Bengine::ResourceManager::getTexture("Textures/Remedy.png");
	static Bengine::GLTexture game = Bengine::ResourceManager::getTexture("Textures/game.png");

	glm::vec4 rectangle = glm::vec4(640,360,1280,720);

	spriteBatch.draw(_KingRect, rotation, uv, King.id, 0.0f, color);
	spriteBatch.draw(_MikeRect, 0, uv, Mike.id, 0.0f, color);
	spriteBatch.draw(_WigiRect, 0, uv, Wigi.id, 0.0f, color);
	spriteBatch.draw(_RemedyRect, 0, uv, Remedy.id, 0.0f, color);
	spriteBatch.draw(_gameRect, 0, uv, game.id, 0.0f, color);
}