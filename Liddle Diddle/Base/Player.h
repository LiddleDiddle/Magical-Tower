#pragma once

#include <SDL2\SDL.h>
#include <unordered_map>
#include <glm\glm.hpp>

class Player
{
public:
	Player(int controllerNumber);
	~Player(void);
	int getControllerNumber() { return _controllerNumber; };
	void setControllerNumber(int controller) { _controllerNumber = controller; };

	 void update();

	void pressKey(unsigned int keyID);
    void releaseKey(unsigned int keyID);

    /// Returns true if the key is held down
    bool isKeyDown(unsigned int keyID);

    /// Returns true if the key was just pressed
    bool isKeyPressed(unsigned int keyID);
	SDL_GameController* getController() {return _controller;};

	float getRightTrigger() {return _rightTrigger;};
	float getLeftTrigger() {return _leftTrigger;};
	glm::vec2 getLeftStick() {return _leftStick;};
	glm::vec2 getRightStick() {return _rightStick;};

	///did the player joing in the character select screen
private:

	/// Returns true if the key is held down
    bool wasKeyDown(unsigned int keyID);
	glm::vec2 _leftStick, _rightStick;
	float _leftTrigger, _rightTrigger;

    std::unordered_map<unsigned int, bool> _keyMap;
    std::unordered_map<unsigned int, bool> _previousKeyMap;

	int _controllerNumber;
	SDL_GameController* _controller;
};

