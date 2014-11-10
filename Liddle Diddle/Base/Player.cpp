#include "Player.h"
#include <iostream>

Player::Player(int controllerNumber) :
	_controllerNumber(controllerNumber)
{
		_controller = SDL_GameControllerOpen(controllerNumber);
}


Player::~Player(void)
{
}

void Player::update() {

	//std::cout << yolo++ << std::endl;
    // Loop through _keyMap using a for each loop, and copy it over to _previousKeyMap
    for (auto& it : _keyMap) {
        _previousKeyMap[it.first] = it.second;
    }
	_leftStick = glm::vec2(SDL_GameControllerGetAxis(_controller,SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f,SDL_GameControllerGetAxis(_controller,SDL_CONTROLLER_AXIS_LEFTY) / -32767.0f);
	_rightStick = glm::vec2(SDL_GameControllerGetAxis(_controller,SDL_CONTROLLER_AXIS_RIGHTX) / 32767.0f,SDL_GameControllerGetAxis(_controller,SDL_CONTROLLER_AXIS_RIGHTY) / -32767.0f);
	_rightTrigger = SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_TRIGGERRIGHT) / 32767.0f;
	_leftTrigger = SDL_GameControllerGetAxis(_controller, SDL_CONTROLLER_AXIS_TRIGGERLEFT) / 32767.0f;
}

void Player::pressKey(unsigned int keyID) {
    // Here we are treating _keyMap as an associative array.
    // if keyID doesn't already exist in _keyMap, it will get added
    _keyMap[keyID] = true;
}

void Player::releaseKey(unsigned int keyID) {
    _keyMap[keyID] = false;
}

bool Player::isKeyDown(unsigned int keyID) {
    // We dont want to use the associative array approach here
    // because we don't want to create a key if it doesnt exist.
    // So we do it manually
    auto it = _keyMap.find(keyID);
    if (it != _keyMap.end()) {
        // Found the key
        return it->second;
    } else {
        // Didn't find the key
        return false;
    }
}

bool Player::isKeyPressed(unsigned int keyID) {
    // Check if it is pressed this frame, and wasn't pressed last frame
    if (isKeyDown(keyID) == true && wasKeyDown(keyID) == false) {
        return true;
    }
    return false;
}

bool Player::wasKeyDown(unsigned int keyID) {
    // We dont want to use the associative array approach here
    // because we don't want to create a key if it doesnt exist.
    // So we do it manually
    auto it = _previousKeyMap.find(keyID);
    if (it != _previousKeyMap.end()) {
        // Found the key
        return it->second;
    } else {
        // Didn't find the key
        return false;
    }
}
