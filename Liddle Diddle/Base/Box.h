#pragma once

#include "GameObject.h"

class Box : public GameObject
{
public:
	Box(b2World* world, float x, float y);
	~Box(void);

	void CreateBox2dObject(float x, float y);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void addForceCenter(float x, float y);
};

