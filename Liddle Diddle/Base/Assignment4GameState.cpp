#include "Assignment4GameState.h"r
#include <iostream>
#include "GameWorld.h"
#include <SDL2/SDL.h>

GameWorld gameWorld;

Assignment4GameState::Assignment4GameState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager)
{

}

void Assignment4GameState::Entered() {
    std::cout << "IntroGameState has been entered" << std::endl;
	gameWorld.CreateBox2DWorld();
}

void Assignment4GameState::Exiting() {
    std::cout << "IntroGameState is exiting" << std::endl;
}

void Assignment4GameState::Update(float elapsedTime, Bengine::InputManager& inputManager) 
{
	gameWorld.Update(elapsedTime / 1000);   //fix this
	
	if (inputManager.isKeyDown(SDLK_SPACE)) {
		gameWorld.OnKeyEvent();
	}
	if (inputManager.isKeyDown(SDLK_r)) {
		gameWorld.endIt();
		this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
	}
}

void Assignment4GameState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	gameWorld.Draw(spriteBatch);
}

