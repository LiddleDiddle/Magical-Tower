#pragma once

#include "GameObject.h"

class Wall : public GameObject
{
public:
	Wall(b2World* world, float x, float y, float w, float h);
	~Wall(void);

	void CreateBox2dObject(float x, float y);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void addForceCenter(float x, float y);
private:
	float posX;
	float posY;
	float width;
	float height;
};

