#include "RemedyMenuState.h"
#include "LevelLoader.h"
#include <SDL2/SDL.h>


RemedyMenuState::RemedyMenuState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

void RemedyMenuState::Entered()
{
	LevelLoader loader;
	XMLDocument xmlDoc;
	loader.DrawLevel(loader.LoadLevel());
}

void RemedyMenuState::Exiting()
{

}

void RemedyMenuState::Update(float elapsedTime, Bengine::InputManager& inputManager)
{

}

void RemedyMenuState::Draw(Bengine::SpriteBatch& spriteBatch)
{

}

void RemedyMenuState::ProcessInput(Bengine::InputManager _inputManager)
{

}

