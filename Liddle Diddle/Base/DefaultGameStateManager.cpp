

#include "DefaultGameStateManager.h"
#include "GameState.h"

#include <stdexcept>

  // ------------------------------------------------------------------------------------------- //

  DefaultGameStateManager::DefaultGameStateManager() {}

  // ------------------------------------------------------------------------------------------- //

  DefaultGameStateManager::~DefaultGameStateManager() {
    while(!this->activeStates.empty()) {
      Pop();
    }
  }

  // ------------------------------------------------------------------------------------------- //

  std::shared_ptr<GameState> DefaultGameStateManager::Peek() const {
    if(this->activeStates.empty()) {
      return std::shared_ptr<GameState>();
    } else {
      return this->activeStates.at(this->activeStates.size() - 1).first;
    }
  }

  // ------------------------------------------------------------------------------------------- //

  void DefaultGameStateManager::Push(
    const std::shared_ptr<GameState> &state, Modality::Enum modality /* = Modality::Exclusive */
  ) {
    this->activeStates.push_back(std::make_pair(state, modality));

    if(modality == Modality::Exclusive) {
      this->exposedDrawables.clear();
      this->exposedUpdateables.clear();
    }

    addToDrawablesOrUpdateables(state.get());

    notifyObscuredStates();

    state->Entered();
  }

  // ------------------------------------------------------------------------------------------- //

  std::shared_ptr<GameState> DefaultGameStateManager::Pop() {
    if(this->activeStates.empty()) {
      throw std::runtime_error("Attempted to pop from an empty game state stack");
    }

    GameStateModalityPair popped = this->activeStates.at(this->activeStates.size() - 1);
    popped.first->Exiting();
    this->activeStates.pop_back();

    if(popped.second == Modality::Exclusive) {
      rebuildUpdateableAndDrawableQueues();
    } else {
      removeFromDrawablesOrUpdateables(popped.first.get());
    }

    notifyRevealedStates();

    return popped.first;
  }

  // ------------------------------------------------------------------------------------------- //

  void DefaultGameStateManager::Update(float elapsedTime, Bengine::InputManager& inputManager) {
    for(std::size_t index = 0; index < this->exposedUpdateables.size(); ++index) {
      this->exposedUpdateables.at(index)->Update(elapsedTime, inputManager);
    }
  }

  // ------------------------------------------------------------------------------------------- //

  void DefaultGameStateManager::Draw(Bengine::SpriteBatch& spriteBatch) {
    for(std::size_t index = 0; index < this->exposedDrawables.size(); ++index) {
      this->exposedDrawables.at(index)->Draw(spriteBatch);
    }
  }

  // ------------------------------------------------------------------------------------------- //

  void DefaultGameStateManager::addToDrawablesOrUpdateables(GameState *gameState) {
    Drawable *drawable = dynamic_cast<Drawable *>(gameState);
    if(drawable) {
      this->exposedDrawables.push_back(drawable);
    }

    Updateable *updateable = dynamic_cast<Updateable *>(gameState);
    if(updateable) {
      this->exposedUpdateables.push_back(updateable);
    }
  }

  // ------------------------------------------------------------------------------------------- //

  void DefaultGameStateManager::removeFromDrawablesOrUpdateables(GameState *gameState) {
    Drawable *drawable = dynamic_cast<Drawable *>(gameState);
    if(drawable) {
      this->exposedDrawables.pop_back();
    }

    Updateable *updateable = dynamic_cast<Updateable *>(gameState);
    if(updateable) {
      this->exposedUpdateables.pop_back();
    }
  }

  // ------------------------------------------------------------------------------------------- //

  void DefaultGameStateManager::rebuildUpdateableAndDrawableQueues() {
    this->exposedUpdateables.clear();
    this->exposedDrawables.clear();

    if(this->activeStates.empty()) {
      return;
    }

    // Reverse scan the active states until we hit either the beginning or an Hiding state
    std::size_t index = this->activeStates.size() - 1;
    while(index > 0) {
      if(this->activeStates.at(index).second == Modality::Exclusive) {
        break;
      }
      --index;
    }

    // Now go forward again and fill the lists of exposed Updateables and Drawables
    while(index < this->activeStates.size()) {
      addToDrawablesOrUpdateables(this->activeStates.at(index).first.get());
      ++index;
    }
  }

  // ------------------------------------------------------------------------------------------- //

  void DefaultGameStateManager::notifyObscuredStates() {
    if(this->activeStates.size() < 2) {
      return;
    }

    // Reverse scan until we hit either the beginning or find the next Hiding state
    std::size_t index = this->activeStates.size() - 2;
    while(index > 0) {
      if(this->activeStates.at(index).second == Modality::Exclusive) {
        break;
      }
      --index;
    }

    // Now go forward (up until the second-to-last state) and notify the obscured states
    while(index < this->activeStates.size() - 1) {
      this->activeStates.at(index).first->Obscuring();
    }
  }

  // ------------------------------------------------------------------------------------------- //

  void DefaultGameStateManager::notifyRevealedStates() {
    if(this->activeStates.empty()) {
      return;
    }

    // Reverse scan until we hit either the beginning or find the next Hiding state
    std::size_t index = this->activeStates.size() - 1;
    while(index > 0) {
      if(this->activeStates.at(index).second == Modality::Exclusive) {
        break;
      }
      --index;
    }

    // Now go forward and notify all revealed state
    while(index < this->activeStates.size()) {
      this->activeStates.at(index).first->Revealed();
    }
  }