#include "StageSelectState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>
#include "MainGame.h"
#include "GeneralManager.h"

const int STAGE_COUNT = 5;

#define CAMERA TheMainGame::Instance()->_camera

StageSelectState::StageSelectState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void StageSelectState::Entered() {
    std::cout << "StageSelectState has been entered" << std::endl;

	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/StageSelect/one.png"));
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/StageSelect/two.png"));
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/StageSelect/three.png"));
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/StageSelect/four.png"));
	_Textures.push_back(Bengine::ResourceManager::getTexture("Textures/StageSelect/five.png"));

	for (int i = 0; i < STAGE_COUNT; i++)
	{
		_menuPositions.emplace_back(CAMERA.getScreenDimensions().x / 2 - CAMERA.getScreenDimensions().x + (CAMERA.getScreenDimensions().x / 2 * i),
			CAMERA.getScreenDimensions().y / 2,
			CAMERA.getScreenDimensions().x / 2,
			CAMERA.getScreenDimensions().y / 2);
	}
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
		for (int i = 0; i < STAGE_COUNT; i++)
		{
			std::swap(_Textures[i],_Textures[(i+1) % STAGE_COUNT]);
		}
	}
	if(TheGeneralManager::Instance()->_players[TheGeneralManager::Instance()->_joinedPlayers[0]].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_LEFT)){
		for (int i = 0; i < STAGE_COUNT; i++)
		{
			if (i == 0)
				std::swap(_Textures[i],_Textures[(STAGE_COUNT - 1) % STAGE_COUNT]);
			else
				std::swap(_Textures[i],_Textures[(i-1)]);
		}
	}
}