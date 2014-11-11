#include "MainGame.h"
#include <Bengine/Errors.h>
#include <Bengine/ResourceManager.h>
#include <iostream>
#include <string>
#include "IntroGameState.h"
#include "GeneralManager.h"
#include "MainMenuGameState.h"

MainGame* MainGame::s_pInstance = 0;

//Constructor, just initializes private member variables
MainGame::MainGame() : 
    _screenWidth(1280),
    _screenHeight(720), 
    _time(0.0f),
    _gameMode(GameMode::PLAY),
    _maxFPS(60.0f),
	_rotation(0.0f),
	gameStateManager(std::make_shared<DefaultGameStateManager>())
{
    _camera.init(_screenWidth, _screenHeight);
	
}
//Destructor
MainGame::~MainGame()
{
}

//This runs the game
void MainGame::run() {
    initSystems();

 
    //This only returns when the game ends
    gameLoop();
}

//Initialize SDL and Opengl and whatever else we need
void MainGame::initSystems() {

    Bengine::init();

    _window.create("Game Engine", _screenWidth, _screenHeight, 0);
	TheGeneralManager::Instance()->init();
    initShaders();

    _spriteBatch.init();
    _fpsLimiter.init(_maxFPS);
	_camera.setPosition(glm::vec2(_screenWidth / 2, _screenHeight / 2));

	// Set the initial game state the game will use after it has started
	std::cout << "*** Pushing intro game state onto the stack ***" << std::endl;
	gameStateManager->Push(std::make_shared<IntroGameState>(gameStateManager));

	
	
}

void MainGame::initShaders() {
    _colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
    _colorProgram.addAttribute("vertexPosition");
    _colorProgram.addAttribute("vertexColor");
    _colorProgram.addAttribute("vertexUV");
    _colorProgram.linkShaders();
}

//This is the main game loop for our program
void MainGame::gameLoop() {

	const float DELTA_TIME = 1.0f/60.0f;
	float currentTime = SDL_GetTicks() / 1000.0f;
	float accumulator = 0.0f;

    //Will loop until we set _gameState to EXIT
    while (_gameMode != GameMode::EXIT) {
       
        _fpsLimiter.begin();
		processInput();
		
		
		TheGeneralManager::Instance()->processPlayerInputs();
        _camera.update();
		
		float newTime = SDL_GetTicks() / 1000.0f;
	   float frameTime = newTime - currentTime;
	   currentTime = newTime;
	   if ( frameTime > 0.25 )
        frameTime = 0.25;
		currentTime = newTime;

	   accumulator += frameTime;

	   while (accumulator >= DELTA_TIME)
	   {
		   gameStateManager->Update(DELTA_TIME, _inputManager);
		   TheGeneralManager::Instance()->updatePlayers();
		   _inputManager.update();
		   accumulator -= DELTA_TIME;
	   }

		
		
		
		drawGame();

        _fps = _fpsLimiter.end();

        //print only once every 10 frames
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 1000) {
            //std::cout << _fps << std::endl;
            frameCounter = 0;
        }
    }
}

//Processes input with SDL
void MainGame::processInput() {
    SDL_Event evnt;

    const float CAMERA_SPEED = 4.0f;
    const float SCALE_SPEED = 0.1f;

    //Will keep looping until there are no more events to process
    while (SDL_PollEvent(&evnt)) {
        switch (evnt.type) {
            case SDL_QUIT:
                _gameMode = GameMode::EXIT;
                break;
            case SDL_MOUSEMOTION:
                _inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
                break;
            case SDL_KEYDOWN:
                _inputManager.pressKey(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.releaseKey(evnt.key.keysym.sym);
                break;
			case SDL_MOUSEBUTTONDOWN:
				_inputManager.pressKey(evnt.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				_inputManager.releaseKey(evnt.button.button);
				break;
        }
    }

	if (_inputManager.isKeyPressed(SDLK_ESCAPE))
	{
		this->gameStateManager->Switch(std::shared_ptr<GameState>(new MainMenuGameState(gameStateManager)));
		return;
	}
	

/*
    if (_inputManager.isKeyPressed(SDLK_w)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }
    if (_inputManager.isKeyPressed(SDLK_s)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
    }
    if (_inputManager.isKeyPressed(SDLK_a)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    }
    if (_inputManager.isKeyPressed(SDLK_d)) {
        _camera.setPosition(_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }
    if (_inputManager.isKeyPressed(SDLK_q)) {
        _camera.setScale(_camera.getScale() + SCALE_SPEED);
    }
    if (_inputManager.isKeyPressed(SDLK_e)) {
        _camera.setScale(_camera.getScale() - SCALE_SPEED);
    }
	if (_inputManager.isKeyPressed(SDL_BUTTON_LEFT)){
	}
	*/
}

//Draws the game using the almighty OpenGL
void MainGame::drawGame() {

    //Set the base depth to 1.0
    glClearDepth(1.0);
    //Clear the color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Enable the shader
    _colorProgram.use();

    //We are using texture unit 0
    glActiveTexture(GL_TEXTURE0);
    //Get the uniform location
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    //Tell the shader that the texture is in texture unit 0
    glUniform1i(textureLocation, 0);

    //Set the camera matrix
    GLint pLocation = _colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = _camera.getCameraMatrix();

    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

    _spriteBatch.begin();

	gameStateManager->Draw(_spriteBatch);

    _spriteBatch.end();

    _spriteBatch.renderBatch();

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable the shader
    _colorProgram.unuse();

    //Swap our buffer and draw everything to the screen!
    _window.swapBuffer();
}    