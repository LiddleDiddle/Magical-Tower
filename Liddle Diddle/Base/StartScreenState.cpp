#include "StartScreenState.h"
#include "MainMenuState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>
#include "GeneralManager.h"

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

void StartScreenState::Update(float elapsedTime, Bengine::InputManager& inputManager) {

	if(inputManager.isKeyPressed(SDLK_SPACE)){
		this->gameStateManager->Switch(std::shared_ptr<GameState>(new MainMenuState(gameStateManager)));
	}

	for (int i = 0; i < TheGeneralManager::Instance()->getNumPlayers(); i++)
	{
		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_A))
		{
			printf("player %i pressed X\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_B))
		{
			printf("player %i pressed circle\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_X))
		{
			printf("player %i pressed square\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_Y))
		{
			printf("player %i pressed Triangle\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_BACK))
		{
			printf("player %i pressed share\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_GUIDE))
		{
			printf("player %i pressed guide\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_START))
		{
			printf("player %i pressed options\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_LEFTSTICK))
		{
			printf("player %i pressed left stick\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_RIGHTSTICK))
		{
			printf("player %i pressed right stick\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
		{
			printf("player %i pressed L1\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
		{
			printf("player %i pressed R1\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_UP))
		{
			printf("player %i pressed up\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
		{
			printf("player %i pressed down\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
		{
			printf("player %i pressed left\n", i);
		}

		if(TheGeneralManager::Instance()->_players[i].isKeyPressed(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
		{
			printf("player %i pressed right\n", i);
		}
	}
}

void StartScreenState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	
	static Bengine::GLTexture bg = Bengine::ResourceManager::getTexture("Textures/StartMenu/bg.png");

	
	spriteBatch.draw(glm::vec4(1280/2,720/2,1280,720), 0, uv, bg.id, 0.0f, color);
}
