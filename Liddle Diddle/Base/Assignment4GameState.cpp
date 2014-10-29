#include "Assignment4GameState.h"
#include <iostream>
#include "GameWorld.h"

GameWorld gameWorld;


Assignment4GameState::Assignment4GameState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{

}

void Assignment4GameState::Entered() {
    std::cout << "IntroGameState has been entered" << std::endl;
	gameWorld.CreateBox2DWorld();
}

void Assignment4GameState::Exiting() {
    std::cout << "IntroGameState is exiting" << std::endl;
}

void Assignment4GameState::Update(float elapsedTime) 
{
	gameWorld.Update(0.01666666f);   //fix this
}

void Assignment4GameState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	gameWorld.Draw(spriteBatch);
}