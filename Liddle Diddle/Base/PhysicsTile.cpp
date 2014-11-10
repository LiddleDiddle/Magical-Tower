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
	tileType = type;
	CreateTile(position);
}

PhysicsTile::~PhysicsTile(void)
{
}

void PhysicsTile::Draw(Bengine::SpriteBatch& spriteBatch)
{

	b2Vec2 position = body->GetPosition();
	float rotation = body->GetAngle();
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	Bengine::ColorRGBA8 color(255,255,255,255);

	static Bengine::GLTexture tile1 = Bengine::ResourceManager::getTexture("Textures/Assignment 4/Box.png");
	static Bengine::GLTexture tile2 = Bengine::ResourceManager::getTexture("Textures/Tile2.png");
	static Bengine::GLTexture tile3 = Bengine::ResourceManager::getTexture("Textures/Tile3.png");

	switch (tileType)
	{
	case 1 :
		spriteBatch.draw(glm::vec4(position.x * CAMERA.getScreenDimensions().x / WIDTH, position.y * CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x/WIDTH, CAMERA.getScreenDimensions().y/HEIGHT), rotation, uv, tile1.id, 0.0f, color);
		break;
	case 2:
		spriteBatch.draw(glm::vec4(position.x * CAMERA.getScreenDimensions().x / WIDTH, position.y * CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x/WIDTH, CAMERA.getScreenDimensions().y/HEIGHT), rotation, uv, tile2.id, 0.0f, color);	
		break;
	case 3:
		spriteBatch.draw(glm::vec4(position.x * CAMERA.getScreenDimensions().x / WIDTH, position.y * CAMERA.getScreenDimensions().y / HEIGHT, CAMERA.getScreenDimensions().x/WIDTH, CAMERA.getScreenDimensions().y/HEIGHT), rotation, uv, tile3.id, 0.0f, color);
		break;
	}
}

void PhysicsTile::CreateTile(b2Vec2 position)
{
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;
	b2PolygonShape staticBox;
	staticBox.SetAsBox(0.5,0.5);

	switch (tileType)
	{
	case 1 :
		bodyDef.type = b2_staticBody;
		fixtureDef.friction = 0.3f;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 0.0f;
		break;
	case 2 :
		bodyDef.type = b2_dynamicBody;
		fixtureDef.friction = 0.3f;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 1.01f;
		break;
	case 3 :
		bodyDef.type = b2_staticBody;
		fixtureDef.friction = 0.0f;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 0.0f;
		break;
	default:
		bodyDef.type = b2_dynamicBody;
		fixtureDef.friction = 0.3f;
		fixtureDef.density = 1.0f;
		fixtureDef.restitution = 0.0f;
		break;
	}
	bodyDef.position.Set(position.x, position.y);

	body = tileWorld->CreateBody(&bodyDef);

	
	

	
	fixtureDef.shape = &staticBox;

	

	body->CreateFixture(&fixtureDef);
}
