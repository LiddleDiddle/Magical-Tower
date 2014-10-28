#pragma once
#include <memory>
#include <string>

  // ------------------------------------------------------------------------------------------- //

  class GameState; // forward declaration so we don't need the header

  // ------------------------------------------------------------------------------------------- //

  class GameStateProvider {

    /// <summary>Destroys the game state manager</summary>
    public: virtual ~GameStateProvider() = 0;

    /// <summary>Provides the state with the specified name</summary>
    /// <param name="name">Name of the game state that will be provided</param>
    /// <returns>A new game or reused game state registered under the specified name</returns>
    public: virtual std::shared_ptr<GameState> GetGameState(const std::string &name) = 0;

 };