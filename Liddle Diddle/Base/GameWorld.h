#pragma once

#include <Box2D\Box2D.h>

#include "GameObject.h"

#include <Bengine\SpriteBatch.h>
#include <Bengine/InputManager.h>

#include <vector>

class GameWorld
{
public:
	GameWorld(void);
	~GameWorld(void);
	
	void CreateBox2DWorld();
	void InitOpenGL(int width, int height);
	void Update(float time);
	void Draw ( Bengine::SpriteBatch& spriteBatch );
	void OnKeyEvent();
private:

	b2World* world;
	std::vector<GameObject*> objects;
	Bengine::InputManager _inputManager;
};

