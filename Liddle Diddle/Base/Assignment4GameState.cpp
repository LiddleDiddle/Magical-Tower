#include "Assignment4GameState.h"
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
	SDL_Event evnt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_KEYDOWN:
			inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		}
	}

	if (inputManager.isKeyPressed(SDLK_SPACE)) {
		gameWorld.OnKeyEvent();
	}
}

void Assignment4GameState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	gameWorld.Draw(spriteBatch);
}

