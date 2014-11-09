#include "ControllerMenuState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>
#include "GeneralManager.h"
#include "MainGame.h"
#include "MultiCharacterSelectState.h"

#define GENERAL_MANAGER TheGeneralManager::Instance()

ControllerMenuState::ControllerMenuState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) {
	
}

void ControllerMenuState::Entered() {
    std::cout << "ControllerMenuState has been entered" << std::endl;
	_numControllers = GENERAL_MANAGER->getNumPlayers();
	_joined = 0;
	GENERAL_MANAGER->_joinedPlayers.clear();
}

void ControllerMenuState::Exiting() {
    std::cout << "ControllerMenuState is exiting" << std::endl;

}

void ControllerMenuState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	ProcessInput(_inputManager);
}

void ControllerMenuState::ProcessInput(Bengine::InputManager _inputManager){
	
	for (int i = 0; i < _numControllers; i++)
	{
		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_A) && _entrants.size() < 4){
			bool check = false;
			for (int j = 0; j < _entrants.size(); j++){
				if(_entrants[j] == i)
					check = true;
			}
			if(check == false)
			{
				_entrants.push_back(i);
				_joined++;
			}
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_B)){
			for (int j = 0; j < _entrants.size(); j++) {
				if(_entrants[j] == i) {
					_entrants.erase(_entrants.begin() + j);
					_joined--;
				}
			}
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_START) && _joined > 0) {
			for (int j = 0; j < _entrants.size(); j++)
			{
				GENERAL_MANAGER->_joinedPlayers.push_back(_entrants[j]);
			}
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new MultiCharacterSelectState(gameStateManager)));
			return;
		}
	}
}

void ControllerMenuState::Draw(Bengine::SpriteBatch& spriteBatch) {
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255,255,255,255);

	static Bengine::GLTexture controller = Bengine::ResourceManager::getTexture("Textures/ControllerMenu/controller.png");
	static Bengine::GLTexture join = Bengine::ResourceManager::getTexture("Textures/ControllerMenu/join.png");
	static Bengine::GLTexture bar = Bengine::ResourceManager::getTexture("Textures/ControllerMenu/BeginBar.png");
	
	for (int i = 0; i < _joined; i++)
	{
		spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x/5 + TheMainGame::Instance()->_camera.getScreenDimensions().x/5 * i,64,128,128), 0, uv, controller.id, 0.0f, color);
	}

	spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x/2,TheMainGame::Instance()->_camera.getScreenDimensions().y*.75,238,185), 0, uv, join.id, 0.0f, color);

	spriteBatch.draw(glm::vec4(TheMainGame::Instance()->_camera.getScreenDimensions().x/2, 128+75,TheMainGame::Instance()->_camera.getScreenDimensions().x,TheMainGame::Instance()->_camera.getScreenDimensions().y / 8.64), 0, uv, bar.id, 0.0f, color);
	
}