#pragma once
#include <Bengine\SpriteBatch.h>
#include <Box2D\Box2D.h>
class PhysicsTile
{
public:
	PhysicsTile(void);
	PhysicsTile(b2World* world, b2Vec2 position, int type);
	~PhysicsTile(void);
	void Draw(Bengine::SpriteBatch& spriteBatch);
	void CreateTile(b2Vec2 position);

private:
	b2Body* body;
	b2World* tileWorld;
	int tileType;
};

