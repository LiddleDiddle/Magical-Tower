#pragma once

#include "GameStateManager.h"
#include "GameState.h"
#include "Updateable.h"
#include "Drawable.h"
#include <Bengine/InputManager.h>
#include <Bengine/Camera2D.h>
#include <Bengine/ResourceManager.h>



class TilemapEditorState : public GameState, public virtual Updateable, public virtual Drawable
{
public:
	/// <summary>Initializes a new intro game state</summary>
	/// <param name="gameStateManager">
	///   Game state manager that will be used to switch to various states
	/// </param>
	TilemapEditorState(const std::shared_ptr<GameStateManager> &gameStateManager);

	/// <summary>Called when the game state is entered</summary>
	void Entered();

	/// <summary>Called when the game state is about to be exited</summary>
	void Exiting();

	/// <summary>Updates the time in the game state's simulation</summary>
	/// <param name="elapsedTime">Time by which to advance the simulation</param>
	void Update(float elapsedTime, Bengine::InputManager& inputManager);

	void Draw(Bengine::SpriteBatch& spriteBatch);
	void ProcessInput(Bengine::InputManager _inputManager);
	void SaveXML(int** level);
	

private: 
	std::shared_ptr<GameStateManager> gameStateManager;
	char* file;
	int** level;
	int** tileChangedArray;
	int bgColor;
	Bengine::GLTexture grids[3];
	int gridNumber;
	int numTiles;
	int sameTile;
	bool mousePressed;
	bool changed;
	bool tempInitialized;
	bool multipleTilesChanged;
	bool firstRun;
	glm::vec2 tileCoords;
	float tempX, tempY;
};
