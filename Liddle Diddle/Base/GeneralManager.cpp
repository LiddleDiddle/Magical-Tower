#include "GeneralManager.h"
#include <iostream>
GeneralManager* GeneralManager::s_pInstance = 0;

GeneralManager::GeneralManager(void)
{

}

void GeneralManager::init()
{
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if(SDL_IsGameController(i));
		{
			std::cout << "Controller " << i << " assigned\n";
			_players.emplace_back(i);
		}
	}
	_numPlayers = _players.size();

	MenuController = -1;

	_levels.emplace_back("Level 1", "Textures/Levels/Level001.png", "Level001.xml");
	_levels.emplace_back("Level 2", "Textures/Levels/Level002.png", "Level002.xml");
	_levels.emplace_back("Level 3", "Textures/Levels/Level003.png", "Level003.xml");
	_levels.emplace_back("Level 4", "Textures/Levels/Level004.png", "Level004.xml");
	_levels.emplace_back("Level 5", "Textures/Levels/Level005.png", "Level005.xml");
	currentLevel = 0;
}

GeneralManager::~GeneralManager(void)
{
}

void GeneralManager::updatePlayers()
{
	for (int i = 0; i < _numPlayers; i++)
	{
		_players[i].update();
	}
}

void GeneralManager::processPlayerInputs(){
	for (int i = 0; i < _players.size(); i++) {	
		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_A) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_A);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_A);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_B) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_B);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_B);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_X) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_X);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_X);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_Y) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_Y);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_Y);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_BACK) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_BACK);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_BACK);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_GUIDE) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_GUIDE);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_GUIDE);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_START) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_START);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_START);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_LEFTSTICK) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_LEFTSTICK);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_LEFTSTICK);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_RIGHTSTICK) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_RIGHTSTICK);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_RIGHTSTICK);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_LEFTSHOULDER) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_DPAD_UP) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_DPAD_UP);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_DPAD_UP);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_DPAD_DOWN);
		}

		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
		}


		if(SDL_GameControllerGetButton(_players[i].getController(),SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1) {
			_players[i].pressKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		} else {
			_players[i].releaseKey(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
		}
	}
}