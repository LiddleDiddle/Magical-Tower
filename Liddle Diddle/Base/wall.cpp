#include "Wall.h"
#include <Bengine\ResourceManager.h>
#include "MainGame.h"

#define CAMERA TheMainGame::Instance()->_camera.getScreenDimensions()
Wall::Wall(b2World* world, float x, float y, float w, float h)
	:GameObject(world),
	posX(x),
	posY(y),
	width(w),
	height(h)
{
	CreateBox2dObject(x,y);
}

Wall::~Wall(void)
{

}

void Wall::CreateBox2dObject(float x, float y)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(posX, posY);

	b2Vec2 v(0, 1.0f);

	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(width/2, height/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.friction = 0.6f;
	fixtureDef.density = 0.0f;
	fixtureDef.restitution = 0.3f;

	body->CreateFixture(&fixtureDef);
}
void Wall::Draw(Bengine::SpriteBatch& spriteBatch)
{
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/Assignment 4/wall.png");
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	glm::vec4 rectangle = glm::vec4(posX * CAMERA.x / 32,posY * CAMERA.y/18,width * CAMERA.x / 32,height * CAMERA.y / 18);

	spriteBatch.draw(rectangle, angle, uv, spook.id, 0.0f, color);

}

void Wall::addForceCenter(float x, float y){
	body->ApplyForceToCenter(b2Vec2(x,y),true);
}