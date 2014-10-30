#pragma once

#include <vector>
#include <utility>

#include "GameStateManager.h"
#include "Drawable.h"
#include "Updateable.h"
#include <Bengine/InputManager.h>

  // ------------------------------------------------------------------------------------------- //

  /// <summary>Stacked game state manager that forwards Draw() and Update() calls</summary>
  /// <remarks>
  ///   <para>
  ///     This game state manager will call the Updateable.Update() and Drawable.Draw() methods
  ///     when any of those interfaces are implemented by the game states pushed onto its stack.
  ///   </para>
  ///   <para>
  ///     To figure out whether a game state implements these interfaces, a dynamic_cast will be
  ///     performed during the Push() call. All active updateables and drawables are then kept
  ///     in separate list, allowing very cheap frame-by-frame processing.
  ///   </para>
  /// </remarks>
  class DefaultGameStateManager : public GameStateManager,
    public virtual Drawable, public virtual Updateable {

    /// <summary>Stores a game state and the modality it was activated with</summary>
    private: typedef std::pair<std::shared_ptr<GameState>, Modality::Enum> GameStateModalityPair;

    /// <summary>Initializes a new game state manager</summary>
    public: DefaultGameStateManager();

    /// <summary>
    ///   Destroys the game state manager, leaving and dropping any active game state
    /// </summary>
    public: virtual ~DefaultGameStateManager();

    /// <summary>Returns the currently active game state</summary>
    /// <returns>The lastmost game state on the stack</returns>
    public: virtual std::shared_ptr<GameState> Peek() const;

    /// <summary>Appends a new game state to the stack</summary>
    /// <param name="state">Game state that will be pushed onto the stack</param>
    /// <param name="modality">Whether the state completely obscures the state below it</param>
    public: virtual void Push(
      const std::shared_ptr<GameState> &state, Modality::Enum modality = Modality::Exclusive
    );

    /// <summary>Removes the lastmost game state from the stack</summary>
    /// <returns>The state that has been removed from the stack</returns>
    public: virtual std::shared_ptr<GameState> Pop();

    /// <summary>Advances the time of the active game states</summary>
    /// <param name="elapsedTime">Elapsed simulation time</param>
  public: void Update(float elapsedTime, Bengine::InputManager& inputManager);

    /// <summary>
    ///   Instructs the active game states to render themselves or to update the scene graph
    /// </summary>
    /// <param name="elapsedFrameTime">Elapsed simulation time at the frame</param>
  public: void Draw(Bengine::SpriteBatch& spriteBatch);

    /// <summary>
    ///   Adds the specified game state to the exposed Drawables or Updateables if it
    ///   implements the Drawable or Updateable interfaces
    /// </summary>
    /// <param name="gameState">
    ///   State that will be checked for implementing the Drawable or Updateable interfaces
    /// </param>
    private: void addToDrawablesOrUpdateables(GameState *gameState);

    /// <summary>
    ///   Removes the specified game state to the exposed Drawables or Updateables if it
    ///   implements the Drawable or Updateable interfaces
    /// </summary>
    /// <param name="gameState">
    ///   State that will be checked for implementing the Drawable or Updateable interfaces
    /// </param>
    private: void removeFromDrawablesOrUpdateables(GameState *gameState);

    /// <summary>
    ///   Rebuilds the separate updateable and drawable queues when an Hiding state has
    ///   been popped from the stack
    /// </summary>
    private: void rebuildUpdateableAndDrawableQueues();

    /// <summary>Notifies all previously exposed states that they have been obscured</summary>
    private: void notifyObscuredStates();

    /// <summary>Notifies all currently exposed states that they have been revealed</summary>
    private: void notifyRevealedStates();

    /// <summary>Stores the currently active game states</summary>
    private: std::vector<GameStateModalityPair> activeStates;
    /// <summary>All drawable game states from the last Hiding state</summary>
    private: std::vector<Drawable *> exposedDrawables;
    /// <summary>All updateable game states from the last Hiding state</summary>
    private: std::vector<Updateable *> exposedUpdateables;

  };