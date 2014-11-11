#pragma once

#include "GameObject.h"

class Pendulum : public GameObject
{
public:
	Pendulum(b2World* world, float x, float y);
	~Pendulum(void);

	void CreateBox2dObject(float x, float y);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void addForceCenter(float x, float y);
};

