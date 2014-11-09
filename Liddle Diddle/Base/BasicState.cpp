#include "BasicState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>

BasicState::BasicState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void BasicState::Entered() {
    std::cout << "_____________ has been entered" << std::endl;  //change this
}

void BasicState::Exiting() {
    std::cout << "_______________ is exiting" << std::endl;  //change this
}

void BasicState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	ProcessInput(_inputManager);
}

void BasicState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	

}

void BasicState::ProcessInput(Bengine::InputManager _inputManager){

}