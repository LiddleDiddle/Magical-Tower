#include "InputManager.h"

namespace Bengine {

InputManager::InputManager(void)
{
}


InputManager::~InputManager(void)
{
}

void InputManager::pressKey(unsigned int keyID){
	_keyMap[keyID] = true;
}

void InputManager::releaseKey(unsigned int keyID){
	_keyMap[keyID] = false;
}

bool InputManager::isKeyPressed(unsigned int keyID){
	auto it = _keyMap.find(keyID);
	if (it != _keyMap.end()) {
		return it->second;
	} else {
		return false;
	}
}

}