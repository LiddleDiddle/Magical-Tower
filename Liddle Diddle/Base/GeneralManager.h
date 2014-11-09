#pragma once

#include "Player.h"
#include <vector>
#include <SDL2\SDL.h>
class GeneralManager
{
public:

	static GeneralManager* Instance()
        {
            if (s_pInstance == 0)
            {
                s_pInstance = new GeneralManager();
            }
            return s_pInstance;
        }
	void init();
	void processPlayerInputs();
	void updatePlayers();
	int getNumPlayers() {return _numPlayers;};
	GeneralManager(void);
	~GeneralManager(void);

	std::vector<Player> _players;
	std::vector<int> _joinedPlayers;
	/// who is in control of the menu 
	int MenuController;

private:
	static GeneralManager* s_pInstance;
	int _numPlayers;
};

typedef GeneralManager TheGeneralManager;