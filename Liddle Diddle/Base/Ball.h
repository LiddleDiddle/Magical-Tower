#pragma once

#include "GameObject.h"

class Ball : public GameObject
{
public:
	Ball(b2World* world, float x, float y);
	~Ball(void);

	void CreateBox2dObject(float x, float y);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void addForceCenter(float x, float y);
};

