#include "TylerMenuState.h"
#include "Assignment4GameState.h"
#include "StartScreenState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include "MainMenuState.h"
#include "MultiCharacterSelectState.h"
#include "MainGame.h"
#include "StageSelectState.h"

#define CAMERA TheMainGame::Instance()->_camera

TylerMenuState::TylerMenuState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{

}

void TylerMenuState::Entered() {
    std::cout << "MainMenuState has been entered" << std::endl;
	for (int i = 0; i < 5; i++)
	{
		_menuPositions.emplace_back(CAMERA.getScreenDimensions().x/8 + CAMERA.getScreenDimensions().x/4 * i,
			CAMERA.getScreenDimensions().y/2,CAMERA.getScreenDimensions().x/4,CAMERA.getScreenDimensions().y);
	}

	
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/TylerMenu/assignment4.png"));
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/TylerMenu/mainMenu.png"));
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/TylerMenu/characterSelect.png"));
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/TylerMenu/anyKey.png"));
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/TylerMenu/stageSelect.png"));
	_mousePressed = true;
}

void TylerMenuState::Exiting() {
    std::cout << "MainMenuState is exiting" << std::endl;
	CAMERA.setPosition(glm::vec2(CAMERA.getScreenDimensions().x/2,CAMERA.getScreenDimensions().y/2));
}

void TylerMenuState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	ProcessInput(_inputManager);
  }

void TylerMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	for (int i = 0; i < _menuPositions.size(); i++)
	{
		spriteBatch.draw(_menuPositions[i], 0, uv, _Textures[i].id, 0.0f, color);
	}
}

void TylerMenuState::ProcessInput(Bengine::InputManager _inputManager){

	const float CAMERA_SPEED = 4.0f;

    if (_inputManager.isKeyPressed(SDLK_a)) {
        CAMERA.setPosition(CAMERA.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    }
    if (_inputManager.isKeyPressed(SDLK_d)) {
        CAMERA.setPosition(CAMERA.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }

	if(CAMERA.getPosition().x <= 640)
		CAMERA.setPosition(glm::vec2(CAMERA.getScreenDimensions().x/2, CAMERA.getScreenDimensions().y/2));
	if(CAMERA.getPosition().x >= _menuPositions.back().x + 160 - 640){
		CAMERA.setPosition(glm::vec2(_menuPositions.back().x + 160 - 640, 360));
	}
	if (_mousePressed == false){
		if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
			_mousePressed = true;
			glm::vec2 mouseCoords = _inputManager.getMouseCoords();
			mouseCoords = CAMERA.convertScreenToWorld(mouseCoords);

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
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new MultiCharacterSelectState(gameStateManager)));
			}
			//four
			if (mouseCoords.x > 1280 - 320 && mouseCoords.x < 1280)
			{
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new StartScreenState(gameStateManager)));
			}
			//five
			if (mouseCoords.x > 1280 && mouseCoords.x < 1280 + 320)
			{
				this->gameStateManager->Switch(std::shared_ptr<GameState>(new StageSelectState(gameStateManager)));
			}
		}
	}
   // std::cout << "MainMenuState updated" << std::endl;
	if (!_inputManager.isKeyPressed(SDL_BUTTON_LEFT))
		_mousePressed = false;
}