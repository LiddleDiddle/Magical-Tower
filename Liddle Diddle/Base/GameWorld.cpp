#include "GameWorld.h"

#include "Box.h"
#include "Ball.h"
#include "Ground.h"
#include <Bengine\ResourceManager.h>
#include <iostream>
GameWorld::GameWorld(void)
{

}


GameWorld::~GameWorld(void)
{
	/*while(objects.size())
	{
		delete objects.back();
		objects.pop_back();
	}
	delete world;*/
}

void GameWorld::endIt(){
	while(objects.size())
	{
		delete objects.back();
		objects.pop_back();
	}
	delete world;
}

void GameWorld::CreateBox2DWorld()
{
	b2Vec2 gravity(0.0f, -10.0f);

	world = new b2World(gravity);

	objects.push_back(new Ground(world));

	objects.push_back(new Box(world, 11.0f, 3));
	objects.push_back(new Box(world, 11.0f, 2));
	objects.push_back(new Box(world, 11.0f, 1));
	objects.push_back(new Ball(world, 9.0f, 2.0f));
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

	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	int count = objects.size();
	for(int i = 0; i < count; i++) objects[i]->Draw(spriteBatch);
}

void GameWorld::OnKeyEvent()
{
	objects.back()->addForceCenter(200,100);
}