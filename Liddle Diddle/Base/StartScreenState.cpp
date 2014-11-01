#include "StartScreenState.h"
#include "MainMenuGameState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>

StartScreenState::StartScreenState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void StartScreenState::Entered() {
    std::cout << "MainMenuState has been entered" << std::endl;
	startRect = glm::vec4(1280/2,100,530,90);
}

void StartScreenState::Exiting() {
    std::cout << "MainMenuState is exiting" << std::endl;
}

void StartScreenState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {

	if(_inputManager.isKeyPressed(SDLK_SPACE))
	{

		this->gameStateManager->Switch(std::shared_ptr<GameState>(new MainMenuGameState(gameStateManager)));
	}
}

void StartScreenState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	
	static Bengine::GLTexture bg = Bengine::ResourceManager::getTexture("Textures/StartMenu/bg.png");

	
	spriteBatch.draw(glm::vec4(1280/2,720/2,1280,720), 0, uv, bg.id, 0.0f, color);
}