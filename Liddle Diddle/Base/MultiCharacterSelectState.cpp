#include "MultiCharacterSelectState.h"
#include "TylerMenuState.h"
#include "MainMenuState.h"
#include "StageSelectState.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <Bengine/ResourceManager.h>
#include "MainMenuState.h"
#include "GeneralManager.h"


#define GENERAL_MANAGER TheGeneralManager::Instance()
const int MAX_PLAYERS = 4;
MultiCharacterSelectState::MultiCharacterSelectState(const std::shared_ptr<GameStateManager> &gameStateManager) :
    gameStateManager(gameStateManager) 
{
	
}

MultiCharacterSelectState::~MultiCharacterSelectState()
{
	delete _character;
	delete _ready;
	delete _joined;


	
}

void MultiCharacterSelectState::Entered() {
    std::cout << "MainMenuState has been entered" << std::endl;
	_one = glm::vec4(160,720/2,320,720);
	_two = glm::vec4(160+320,720/2,320,720);
	_three = glm::vec4(160+320*2,720/2,320,720);
	_four = glm::vec4(160+320*3,720/2,320,720);
	_mousePressed = true;

	_ready = new bool[4];
	_character = new int[4];
	_direction = new Direction[4];
	_joined = new bool[4];
	for (int i = 0; i < 4; i++)
	{
		_ready[i] = false;
		_joined[i] = false;
		_character[i] = i;
		_direction[i] = Direction::NEUTRAL;
	}
	
	_numPlayers = TheGeneralManager::Instance()->getNumPlayers();
}

void MultiCharacterSelectState::Exiting() {
    std::cout << "MainMenuState is exiting" << std::endl;
}

void MultiCharacterSelectState::Update(float elapsedTime, Bengine::InputManager& _inputManager) {
	
}

void MultiCharacterSelectState::Draw(Bengine::SpriteBatch& spriteBatch)
{
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	Bengine::ColorRGBA8 green;
	green.r = 0;
    green.g = 255;
    green.b = 0;
    green.a = 255;

	static Bengine::GLTexture bg = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/blankBG.png");
	static Bengine::GLTexture join = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/join.png");

	//characters
	static Bengine::GLTexture misaka = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/misaka.png");
	static Bengine::GLTexture ghoul = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/ghoul.png");
	static Bengine::GLTexture peach = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/peach.png");
	static Bengine::GLTexture gorilla = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/gorilla.png");

	static Bengine::GLTexture ready = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/ready.png");
	static Bengine::GLTexture border = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/border.png");
	static Bengine::GLTexture arrow = Bengine::ResourceManager::getTexture("Textures/CharacterSelect/arrowUp.png");

	for (int i = 0; i < 4; i++)
	{
		spriteBatch.draw(glm::vec4(160 + 320 * i,360,320,720), 0, uv, border.id, 0.0f, color);
		if(!_joined[i])
		{
			spriteBatch.draw(glm::vec4(160 + 320 * i,360,320,720), 0, uv, bg.id, 0.0f, color);
			spriteBatch.draw(glm::vec4(160 + 320 * i,360,238,185), 0, uv, join.id, -1.0f, color);
		}
		if(_joined[i])
		{
			
			switch (_character[i] % 4)
			{
			case 0:
				spriteBatch.draw(glm::vec4(160 + 320 * i,360,320,720), 0, uv, misaka.id, 0.0f, color);
				break;
			case 1:
				spriteBatch.draw(glm::vec4(160 + 320 * i,360,320,720), 0, uv, ghoul.id, 0.0f, color);
				break;
			case 2:
				spriteBatch.draw(glm::vec4(160 + 320 * i,360,320,720), 0, uv, peach.id, 0.0f, color);
				break;
			case 3:
				spriteBatch.draw(glm::vec4(160 + 320 * i,360,320,720), 0, uv, gorilla.id, 0.0f, color);
				break;
			}

			switch (_direction[i])
			{
			case Direction::NEUTRAL:
				spriteBatch.draw(glm::vec4(160 + 320 * i,720-35,60,30), 0, uv, arrow.id, 0.0f, color);
				spriteBatch.draw(glm::vec4(160 + 320 * i,35,60,30), 3.14159265359, uv, arrow.id, 0.0f, color);
				break;
			case Direction::UP:
				spriteBatch.draw(glm::vec4(160 + 320 * i,720-35,60,30), 0, uv, arrow.id, 0.0f, green);
				spriteBatch.draw(glm::vec4(160 + 320 * i,35,60,30), 3.14159265359, uv, arrow.id, 0.0f, color);
				break;
			case Direction::DOWN:
				spriteBatch.draw(glm::vec4(160 + 320 * i,720-35,60,30), 0, uv, arrow.id, 0.0f, color);
				spriteBatch.draw(glm::vec4(160 + 320 * i,35,60,30), 3.14159265359, uv, arrow.id, 0.0f, green);
				break;
			}
		}
		if(_ready[i])
		{
		spriteBatch.draw(glm::vec4(160 + 320 * i,360,250,250), 0, uv, ready.id, 0.0f, color);
		}
	}
}