#pragma once

#include <Bengine\SpriteBatch.h>

  /// <summary>Can be implemented by game states to be notified of Draw() calls</summary>
  class Drawable {

    
    public: virtual ~Drawable() {}

    /// <summary>Called when the game state should draw itself</summary>
  public: virtual void Draw(Bengine::SpriteBatch& spriteBatch) = 0;

  };
