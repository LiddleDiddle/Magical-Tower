#pragma once

#include "GameStateManager.h"
#include "GameState.h"
#include "Updateable.h"
#include "Drawable.h"
#include <Bengine/InputManager.h>
#include <memory>

enum class Direction{
	NEUTRAL,
	UP,
	DOWN
};

class MultiCharacterSelectState : public GameState, public virtual Updateable, public virtual Drawable
{
public:
	/// <summary>Initializes a new intro game state</summary>
	/// <param name="gameStateManager">
	///   Game state manager that will be used to switch to various states
	/// </param>
	MultiCharacterSelectState(const std::shared_ptr<GameStateManager> &gameStateManager);
	~MultiCharacterSelectState();
	/// <summary>Called when the game state is entered</summary>
	void Entered();

	/// <summary>Called when the game state is about to be exited</summary>
	public: void Exiting();

	/// <summary>Updates the time in the game state's simulation</summary>
	/// <param name="elapsedTime">Time by which to advance the simulation</param>
	void Update(float elapsedTime, Bengine::InputManager& inputManager);

	void Draw(Bengine::SpriteBatch& spriteBatch);
	void ProcessInput();


private: 
	
	bool* _joined;
	bool* _ready;
	int* _character;
	int _numPlayers;
	Direction* _direction;


	std::shared_ptr<GameStateManager> gameStateManager;

	glm::vec4 _one;
	glm::vec4 _two;
	glm::vec4 _three;
	glm::vec4 _four;

	
	bool _mousePressed;
};
