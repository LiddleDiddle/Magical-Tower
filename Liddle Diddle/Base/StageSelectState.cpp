#include "StageSelectState.h"
#include "Level.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>
#include "MainGame.h"
#include "GeneralManager.h"
#include "RemedyMenuState.h"

#define CAMERA TheMainGame::Instance()->_camera

StageSelectState::StageSelectState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void StageSelectState::Entered() {
    std::cout << "StageSelectState has been entered" << std::endl;
	for (int i = 0; i < TheGeneralManager::Instance()->_levels.size(); i++)
	{
			_Textures.push_back(Bengine::ResourceManager::getTexture(TheGeneralManager::Instance()->_levels[i].GetImage()));
	}

	for (int i = 0; i < TheGeneralManager::Instance()->_levels.size(); i++)
	{
		_menuPositions.emplace_back(CAMERA.getScreenDimensions().x / 2 - CAMERA.getScreenDimensions().x + (CAMERA.getScreenDimensions().x / 2 * i),
			CAMERA.getScreenDimensions().y / 2,
			CAMERA.getScreenDimensions().x / 2,
			CAMERA.getScreenDimensions().y / 2);
	}
	currentLevel = 2;
}

void StageSelectState::Exiting() {
    std::cout << "StageSelectState is exiting" << std::endl;
}

void StageSelectState::Update(float elapsedTime, Bengine::InputManager& inputManager) {
	ProcessInput(inputManager);
	
}

void StageSelectState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	
	for (int i = 0; i < 5; i++)
	{
		spriteBatch.draw(_menuPositions[i], 0, uv, _Textures[i].id, 0.0f, color);
	}
}

void StageSelectState::ProcessInput(Bengine::InputManager inputManager){
	if(TheGeneralManager::Instance()->_players[TheGeneralManager::Instance()->_joinedPlayers[0]].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)){
		for (int i = 0; i < TheGeneralManager::Instance()->_levels.size()-1; i++)
		{
			std::swap(_Textures[i],_Textures[i+1]);

		}
			currentLevel++;
			if(currentLevel > TheGeneralManager::Instance()->_levels.size() - 1)
				currentLevel = 0;
	}
	if(TheGeneralManager::Instance()->_players[TheGeneralManager::Instance()->_joinedPlayers[0]].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_LEFT)){
		for (int i = TheGeneralManager::Instance()->_levels.size() - 1; i > 0 ; i--)
		{
				std::swap(_Textures[i],_Textures[(i-1)]);
		}
		currentLevel--;
		if(currentLevel < 0)
			currentLevel = TheGeneralManager::Instance()->_levels.size() - 1;
		std::cout <<currentLevel << std::endl;
	}

	if(TheGeneralManager::Instance()->_players[TheGeneralManager::Instance()->_joinedPlayers[0]].isKeyPressed(SDL_CONTROLLER_BUTTON_A)){
		TheGeneralManager::Instance()->currentLevel = currentLevel;
		std::cout << "Level " << currentLevel << " selected!" <<std::endl;
		this->gameStateManager->Switch(std::shared_ptr<GameState>(new RemedyMenuState(gameStateManager)));
	}

	
}