#include "TylerMenuState.h"
#include "Assignment4GameState.h"
#include "StartScreenState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>
#include "MainMenuState.h"

TylerMenuState::TylerMenuState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void TylerMenuState::Entered() {
    std::cout << "MainMenuState has been entered" << std::endl;
	_one = glm::vec4(160,720/2,320,720);
	_two = glm::vec4(160+320,720/2,320,720);
	_three = glm::vec4(160+320*2,720/2,320,720);
	_four = glm::vec4(160+320*3,720/2,320,720);
	_mousePressed = true;
}

void TylerMenuState::Exiting() {
    std::cout << "MainMenuState is exiting" << std::endl;
}

void TylerMenuState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	if (_mousePressed == false){
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
			_mousePressed = true;
			glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			mouseCoords.y = 720 - mouseCoords.y;

			//one
			if (mouseCoords.x > 0 && mouseCoords.x < 320)
			{
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
			}
			//two
			if (mouseCoords.x > 320 && mouseCoords.x < 640)
			{
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new MainMenuState(gameStateManager)));
			}
			//three
			if (mouseCoords.x > 640 && mouseCoords.x < 960)
			{
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new StartScreenState(gameStateManager)));
			}
			//four
			if (mouseCoords.x > 1280 - 320 && mouseCoords.x < 1280)
			{
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new StartScreenState(gameStateManager)));
			}
		}
	}
   // std::cout << "MainMenuState updated" << std::endl;
	if (!_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
		_mousePressed = false;
  }

void TylerMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	static Bengine::GLTexture King = Bengine::ResourceManager::getTexture("Textures/TylerMenu/assignment4.png");
	static Bengine::GLTexture anyKey = Bengine::ResourceManager::getTexture("Textures/TylerMenu/anyKey.png");
	static Bengine::GLTexture mainMenu = Bengine::ResourceManager::getTexture("Textures/TylerMenu/mainMenu.png");
	static Bengine::GLTexture characterSelect = Bengine::ResourceManager::getTexture("Textures/TylerMenu/characterSelect.png");
	spriteBatch.draw(_one, 0, uv, King.id, 0.0f, color);
	spriteBatch.draw(_two, 0, uv, mainMenu.id, 0.0f, color);
	spriteBatch.draw(_three, 0, uv, characterSelect.id, 0.0f, color);
	spriteBatch.draw(_four, 0, uv, anyKey.id, 0.0f, color);
}