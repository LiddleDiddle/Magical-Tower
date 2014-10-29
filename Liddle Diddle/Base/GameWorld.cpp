#include "GameWorld.h"

#include "Box.h"
#include "Ball.h"
#include "Ground.h"

GameWorld::GameWorld(void)
{

}


GameWorld::~GameWorld(void)
{
	while(objects.size())
	{
		delete objects.back();
		objects.pop_back();
	}
}

void GameWorld::CreateBox2DWorld()
{
	b2Vec2 gravity(0.0f, -10.0f);

	world = new b2World(gravity);

	objects.push_back(new Ground(world));

	objects.push_back(new Box(world, 0.0f, 40.0f));
	objects.push_back(new Ball(world, -1.0f, 10.0f));
}

void GameWorld::InitOpenGL(int width, int height)
{
	//not needed as of right now
}

void GameWorld::Update(float time)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(time, velocityIterations, positionIterations);
}

void GameWorld::Draw ( Bengine::SpriteBatch& spriteBatch )
{
	int count = objects.size();
	for(int i = 0; i < count; i++) objects[i]->Draw(spriteBatch);
}

void GameWorld::OnKeyEvent()
{

}