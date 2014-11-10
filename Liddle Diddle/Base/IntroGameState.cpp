#include "IntroGameState.h"
#include <iostream>
#include "MainMenuGameState.h"
#include <Bengine\ResourceManager.h>
IntroGameState::IntroGameState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{

}

void IntroGameState::Entered() {
    std::cout << "IntroGameState has been entered" << std::endl;
	_time = 0.0f;
	_startTime = false;
}

void IntroGameState::Exiting() {
    std::cout << "IntroGameState is exiting" << std::endl;
}

void IntroGameState::Update(float elapsedTime, Bengine::InputManager& inputManager) {
    if(_startTime)
		_time += elapsedTime;
	else
		_startTime = true;
	if(_time >= 2)
		this->gameStateManager->Switch(std::shared_ptr<GameState>(new MainMenuGameState(gameStateManager)));
  }

void IntroGameState::Draw(Bengine::SpriteBatch& spriteBatch)
{

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/Logo.png");
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	glm::vec4 rectangle = glm::vec4(640,360,1280,720);

	spriteBatch.draw(rectangle, 0, uv, spook.id, 0.0f, color);
}