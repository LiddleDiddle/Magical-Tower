#include "MainMenuGameState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>
#include "Assignment4GameState.h"
MainMenuGameState::MainMenuGameState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void MainMenuGameState::Entered() {
    std::cout << "MainMenuState has been entered" << std::endl;
	_WigiRect = glm::vec4(200,720-150,200,100);
	_MikeRect = glm::vec4(200,150,200,100);
	_KingRect = glm::vec4(1080,720-150,200,100);
	_RemedyRect = glm::vec4(1080,150,200,100);
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
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
		glm::vec2 mouseCoords = _inputManager.getMouseCoords();
		mouseCoords.y = 720 - mouseCoords.y;
		if (mouseCoords.x < _WigiRect.x + 100 && mouseCoords.x > _WigiRect.x -100 && mouseCoords.y > _WigiRect.y - 50 && mouseCoords.y < _WigiRect.y +50)
		{
			//this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
			std::cout << "Wigi\n"; 
		}
		if (mouseCoords.x < _MikeRect.x + 100 && mouseCoords.x > _MikeRect.x -100 && mouseCoords.y > _MikeRect.y - 50 && mouseCoords.y < _MikeRect.y +50)
		{
			//this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
			std::cout << "Mike\n"; 
		}
		if (mouseCoords.x < _RemedyRect.x + 100 && mouseCoords.x > _RemedyRect.x -100 && mouseCoords.y > _RemedyRect.y - 50 && mouseCoords.y < _RemedyRect.y +50)
		{
			//this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
			std::cout << "Remedy\n"; 
		}
		if (mouseCoords.x < _KingRect.x + 100 && mouseCoords.x > _KingRect.x -100 && mouseCoords.y > _KingRect.y - 50 && mouseCoords.y < _KingRect.y +50)
		{
			this->gameStateManager->Switch(std::shared_ptr<GameState>(new Assignment4GameState(gameStateManager)));
		}
	}
	
   // std::cout << "MainMenuState updated" << std::endl;
	
  }

void MainMenuGameState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	static Bengine::GLTexture King = Bengine::ResourceManager::getTexture("Textures/King.png");
	static Bengine::GLTexture Mike = Bengine::ResourceManager::getTexture("Textures/Mike.png");
	static Bengine::GLTexture Wigi = Bengine::ResourceManager::getTexture("Textures/Wigi.png");
	static Bengine::GLTexture Remedy = Bengine::ResourceManager::getTexture("Textures/Remedy.png");


	glm::vec4 rectangle = glm::vec4(640,360,1280,720);

	spriteBatch.draw(_KingRect, 0, uv, King.id, 0.0f, color);
	spriteBatch.draw(_MikeRect, 0, uv, Mike.id, 0.0f, color);
	spriteBatch.draw(_WigiRect, 0, uv, Wigi.id, 0.0f, color);
	spriteBatch.draw(_RemedyRect, 0, uv, Remedy.id, 0.0f, color);
}