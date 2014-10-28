#include "MainMenuGameState.h"
#include <iostream>

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

void MainMenuGameState::Update(float elapsedTime) {
    std::cout << "MainMenuState updated" << std::endl;
  }