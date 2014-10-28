#pragma once

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <Bengine/Bengine.h>
#include <Bengine/GLSLProgram.h>
#include <Bengine/GLTexture.h>
#include <Bengine/Sprite.h>
#include <Bengine/Window.h>
#include <Bengine/InputManager.h>
#include <Bengine/Timing.h>
#include <Bengine/SpriteBatch.h>
#include <Bengine/Camera2D.h>
#include "Bullet.h"
#include "GameStateManager.h"
#include "DefaultGameStateManager.h"

#include <vector>

enum class GameMode {PLAY, EXIT};

//Our example game class, just for testing purposes right now
class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();
	glm::vec2 getScreenDimensions() { return glm::vec2(_screenWidth, _screenHeight); };
private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();

    Bengine::Window _window;

    int _screenWidth;
    int _screenHeight;

    GameMode _gameMode;

    Bengine::GLSLProgram _colorProgram;
    Bengine::Camera2D _camera;
    Bengine::SpriteBatch _spriteBatch;
    Bengine::InputManager _inputManager;
    Bengine::FpsLimiter _fpsLimiter;
    
	std::vector<Bullet> _bullets;

    float _maxFPS;
    float _fps;
    float _time;
	float _rotation;
	std::shared_ptr<DefaultGameStateManager> gameStateManager;
};

