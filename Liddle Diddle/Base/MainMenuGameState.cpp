#include "MainMenuGameState.h"
#include <iostream>
#include <SDL2/SDL.h>

MainMenuGameState::MainMenuGameState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void MainMenuGameState::Entered() {
    std::cout << "MainMenuState has been entered" << std::endl;
}

void MainMenuGameState::Exiting() {
    std::cout << "MainMenuState is exiting" << std::endl;
}

void MainMenuGameState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {

	SDL_Event evnt;

    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {

            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.releaseKey(evnt.key.keysym.sym);
                break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(evnt.button.button);
				break;
        }
    }
	if (_inputManager.isKeyPressed(SDLK_SPACE))
	{
		std::cout << "Pressed space\n";
	}
	
   // std::cout << "MainMenuState updated" << std::endl;
	
  }

void MainMenuGameState::Draw(Bengine::SpriteBatch& spriteBatch)
{

}