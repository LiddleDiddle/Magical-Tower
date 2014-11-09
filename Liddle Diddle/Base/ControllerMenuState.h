#pragma once

#include "GameStateManager.h"
#include "GameState.h"
#include "Updateable.h"
#include "Drawable.h"
#include <Bengine/InputManager.h>
#include <memory>



class ControllerMenuState : public GameState, public virtual Updateable, public virtual Drawable
{
public:
	ControllerMenuState(const std::shared_ptr<GameStateManager> &gameStateManager);

	void Entered();

	public: void Exiting();

	void Update(float elapsedTime, Bengine::InputManager& inputManager);

	void Draw(Bengine::SpriteBatch& spriteBatch);
	void ProcessInput(Bengine::InputManager _inputManager);


private: 
	int _numControllers;
	int _joined;
	std::vector<int> _entrants;
	std::shared_ptr<GameStateManager> gameStateManager;

};