#include "GameWorld.h"

#include "Box.h"
#include "Ball.h"
#include "Ground.h"
#include "wall.h"
#include "Seesaw.h"
#include "Pendulum.h"
#include <Bengine\ResourceManager.h>
#include <iostream>
#include <SDL2\SDL.h>
b2MouseJoint* m_mouseJoint;
b2Vec2 m_mouseWorld;

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
	delete world;
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

	objects.push_back(new Wall(world, 16, .5f, 32, 1));
	objects.push_back(new Wall(world, 16, 17.5f, 32, 1));
	objects.push_back(new Wall(world, 5, 9, 10, 16));
	objects.push_back(new Wall(world, 27, 9, 10, 16));
	objects.push_back(new Seesaw(world, 16, 4, 10, 1));
	objects.push_back(new Box(world, 19, 7));
	objects.push_back(new Pendulum(world, 12, 17.5));
	objects.push_back(new Pendulum(world, 14, 17.5));
	objects.push_back(new Pendulum(world, 16, 17.5));
	objects.push_back(new Pendulum(world, 18, 17.5));
	objects.push_back(new Pendulum(world, 20, 17.5));

	b2BodyDef bodyDef;
	m_groundBody = world->CreateBody(&bodyDef);
	isMouseDown = false;
}

void GameWorld::InitOpenGL(int width, int height)
{
	//not needed as of right now
}

void GameWorld::Update(float time, Bengine::InputManager inputManager)
{
	
	
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(time, velocityIterations, positionIterations);

	if(!inputManager.isKeyDown(SDL_BUTTON_LEFT) && isMouseDown)
	{
		if (m_mouseJoint)
	{
		world->DestroyJoint(m_mouseJoint);
		m_mouseJoint = NULL;
	}
	
	}

	if (isMouseDown == true)
	{
		b2Vec2 p = b2Vec2(inputManager.getMouseCoords().x / 40.0f,18 -(inputManager.getMouseCoords().y / 40.0f));
		m_mouseWorld = p;
	
		if (m_mouseJoint)
		{
			m_mouseJoint->SetTarget(p);
		}
	}

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
	objects.back()->addForceCenter(500,500);
}

void GameWorld::mouseDown(const b2Vec2& p)
{
	m_mouseWorld = p;
	
	if (m_mouseJoint != NULL)
	{
		return;
	}
	printf("x: %f,y: %f\n",p.x,p.y); 
	// Make a small box.
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = p - d;
	aabb.upperBound = p + d;

	// Query the world for overlapping shapes.
	QueryCallback callback(p);
	world->QueryAABB(&callback, aabb);

	if (callback.m_fixture)
	{
		b2Body* body = callback.m_fixture->GetBody();
		b2MouseJointDef md;
		md.bodyA = m_groundBody;
		md.bodyB = body;
		md.target = p;
		md.maxForce = 1000.0f * body->GetMass();
		m_mouseJoint = (b2MouseJoint*)world->CreateJoint(&md);
		body->SetAwake(true);
		isMouseDown = true;
	}
}