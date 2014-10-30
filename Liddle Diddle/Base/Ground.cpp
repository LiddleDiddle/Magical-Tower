#include "Ground.h"
#include <iostream>


Ground::Ground(b2World* world)
	:GameObject(world)
{
	CreateBox2dObject(0, 0);
}


Ground::~Ground(void)
{
}

void Ground::CreateBox2dObject(float x, float y)
{
	// Define the ground body.
	b2BodyDef groundBodyDef;	
	//groundBodyDef.position.Set(0.0f, -10.0f);
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	body = world->CreateBody(&groundBodyDef);

	// Version 2.2.1
	b2EdgeShape groundBox;
	// The extents are the half-widths of the box.
	
	groundBox.Set(b2Vec2(30.0f, 0.0f), b2Vec2(0.0f, 0.0f));

	// Add the ground fixture to the ground body.
	body->CreateFixture(&groundBox, 0.0f);
}

void Ground::Draw(Bengine::SpriteBatch& spriteBatch)
{

}

void Ground::addForceCenter(float x, float y){
	body->ApplyForceToCenter(b2Vec2(x,y),true);
}