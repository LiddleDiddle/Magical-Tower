#pragma once

#include "GameStateManager.h"
#include "gamestate.h"
#include "Updateable.h"
#include "Drawable.h"
#include <memory>
class MainMenuState : public GameState, public virtual Updateable, public virtual Drawable
{
public:
	/// <summary>Initializes a new intro game state</summary>
	/// <param name="gameStateManager">
	///   Game state manager that will be used to switch to the main menu when
	///   the introduction has finished
	/// </param>
	MainMenuState(const std::shared_ptr<GameStateManager> &gameStateManager);

	/// <summary>Called when the game state is entered</summary>
	void Entered();

	/// <summary>Called when the game state is about to be exited</summary>
	public: void Exiting();

	/// <summary>Updates the time in the game state's simulation</summary>
	/// <param name="elapsedTime">Time by which to advance the simulation</param>
	void Update(float elapsedTime, Bengine::InputManager& inputManager);

	void Draw(Bengine::SpriteBatch& spriteBatch);
	void checkCollision(Bengine::InputManager inputManager);
	void processControllerInputs();
private: 
	std::shared_ptr<GameStateManager> gameStateManager;
	glm::vec4* rects;
	float _time;
	int _hover;
	int _currentlyHighlighted;
};

