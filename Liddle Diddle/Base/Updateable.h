#pragma once

  /// <summary>Can be implemented by game states to be notified of Update() calls</summary>
class Updateable {

    /// <summary>Destroys the updateable object</summary>
    public: virtual ~Updateable() {}

    /// <summary>Called when the game state should advance its simulation state</summary>
    public: virtual void Update(float elapsedTime) = 0;

};
