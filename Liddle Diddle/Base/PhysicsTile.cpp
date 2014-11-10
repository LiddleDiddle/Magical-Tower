#include "PhysicsTile.h"
#include <Bengine/ResourceManager.h>
#include "MainGame.h"

#define CAMERA TheMainGame::Instance()->_camera
#define WIDTH 32
#define HEIGHT 18

PhysicsTile::PhysicsTile(void)
{

}

PhysicsTile::PhysicsTile(b2World* world, b2Vec2 position, int type)
{
	tileWorld = world;
	CreateTile(position);
	tileType = type;
}


PhysicsTile::~PhysicsTile(void)
{
}

void PhysicsTile::Draw(Bengine::SpriteBatch& spriteBatch)
{

	b2Vec2 position = body->GetPosition();

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	static Bengine::GLTexture tile1 = Bengine::ResourceManager::getTexture("Textures/Assignment 4/Box.png");
	static Bengine::GLTexture tile2 = Bengine::ResourceManager::getTexture("Textures/Tile2.png");
	static Bengine::GLTexture tile3 = Bengine::ResourceManager::getTexture("Textures/Tile3.png");

	if (tileType == 1)
	{
		spriteBatch.draw(glm::vec4(position.x, position.y, CAMERA.getScreenDimensions().x/WIDTH, CAMERA.getScreenDimensions().y/HEIGHT), 0.0f, uv, tile1.id, 0.0f, color);
	}
	else if (tileType == 2)
	{
		spriteBatch.draw(glm::vec4(position.x, position.y, CAMERA.getScreenDimensions().x/WIDTH, CAMERA.getScreenDimensions().y/HEIGHT), 0.0f, uv, tile2.id, 0.0f, color);	
	}
	else if (tileType == 3)
	{
		spriteBatch.draw(glm::vec4(position.x, position.y, CAMERA.getScreenDimensions().x/WIDTH, CAMERA.getScreenDimensions().y/HEIGHT), 0.0f, uv, tile3.id, 0.0f, color);	
	}
}

void PhysicsTile::CreateTile(b2Vec2 position)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(position.x, position.y);

	body = tileWorld->CreateBody(&bodyDef);

	b2PolygonShape staticBox;
	staticBox.SetAsBox(CAMERA.getScreenDimensions().x/WIDTH/2, CAMERA.getScreenDimensions().x/HEIGHT/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &staticBox;

	fixtureDef.friction = 0.0f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.5f;

	body->CreateFixture(&fixtureDef);
}
