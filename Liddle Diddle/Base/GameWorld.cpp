#include "GameWorld.h"

#include "Box.h"
#include "Ball.h"
#include "Ground.h"

#include <SDL2/SDL.h>

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

	objects.push_back(new Box(world, 11.0f, 3));
	objects.push_back(new Box(world, 11.0f, 2));
	objects.push_back(new Box(world, 11.0f, 1));
	objects.push_back(new Ball(world, 0.0f, 2.0f));

	
}

void GameWorld::InitOpenGL(int width, int height)
{
	//not needed as of right now
}

void GameWorld::Update(float time)
{
	OnKeyEvent();

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
	SDL_Event evnt;

	const float CAMERA_SPEED = 4.0f;
	const float SCALE_SPEED = 0.1f;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_MOUSEMOTION:
			_inputManager.setMouseCoords(evnt.motion.x, evnt.motion.y);
			break;
		case SDL_KEYDOWN:
			_inputManager.pressKey(evnt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			_inputManager.releaseKey(evnt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			_inputManager.pressKey(evnt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			_inputManager.releaseKey(evnt.button.button);
			break;
		}
	}

	if (_inputManager.isKeyPressed(SDLK_SPACE)) {
	}
}