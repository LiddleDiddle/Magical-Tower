#pragma once

#include <Box2D\Box2D.h>
#include <Bengine\SpriteBatch.h>
class GameObject
{
public:
	GameObject(b2World* world);
	virtual ~GameObject(void);

	virtual void CreateBox2dObject(float x, float y) = 0;
	virtual void Draw(Bengine::SpriteBatch& spriteBatch) = 0;
	virtual void addForceCenter(float x, float y) = 0;
protected:
	b2Body* body;
	b2World* world;
};

