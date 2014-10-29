#pragma once

class Inputable {

	public: virtual ~Inputable() {}

    /// <summary>Called if the game state allows input</summary>
  public: virtual void ProcessInput() = 0;

  };