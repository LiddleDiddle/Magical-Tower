#include "StageSelectState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>

StageSelectState::StageSelectState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void StageSelectState::Entered() {
    std::cout << "StageSelectState has been entered" << std::endl;
}

void StageSelectState::Exiting() {
    std::cout << "StageSelectState is exiting" << std::endl;
}

void StageSelectState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	ProcessInput(_inputManager);
}

void StageSelectState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	

}

void StageSelectState::ProcessInput(Bengine::InputManager _inputManager){

}