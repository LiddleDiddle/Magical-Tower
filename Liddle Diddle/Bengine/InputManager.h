#pragma once

#include <unordered_map>

namespace Bengine {

class InputManager
{
public:
	InputManager(void);
	~InputManager(void);

	void pressKey(unsigned int keyID);

	void releaseKey(unsigned int keyID);

	bool isKeyPressed(unsigned int keyID);

private:

	std::unordered_map<unsigned int, bool> _keyMap;
};

}