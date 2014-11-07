#pragma once

#include <SDL2\SDL.h>
#include <unordered_map>

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
private:
	/// Returns true if the key is held down
    bool wasKeyDown(unsigned int keyID);


    std::unordered_map<unsigned int, bool> _keyMap;
    std::unordered_map<unsigned int, bool> _previousKeyMap;

	int _controllerNumber;
	SDL_GameController* _controller;
};

