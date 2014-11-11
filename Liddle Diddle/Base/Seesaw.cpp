#include "Seesaw.h"
#include <Bengine\ResourceManager.h>
#include "MainGame.h"

#define CAMERA TheMainGame::Instance()->_camera.getScreenDimensions()
Seesaw::Seesaw(b2World* world, float x, float y, float w, float h)
	:GameObject(world),
	posX(x),
	posY(y),
	width(w),
	height(h)
{
	CreateBox2dObject(x,y);
}

Seesaw::~Seesaw(void)
{

}

void Seesaw::CreateBox2dObject(float x, float y)
{

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(posX, posY);

	b2Vec2 v(0, 1.0f);

	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(width/2, height/2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.friction = 1.0f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.3f;

	body->CreateFixture(&fixtureDef);

	// Circle
	b2CircleShape shape;
	shape.m_radius = height / 2;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.restitution = 0.7f;
	fd.friction = 0.3f;
	b2BodyDef bd;
	bd.type = b2_staticBody;
	//bd.position.Set(-1.0f , 20.0f);
	bd.position.Set(posX, posY);
	body2 = world->CreateBody(&bd);			
	body2->CreateFixture(&fd);

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = body;
	revoluteJointDef.bodyB = body2;
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.localAnchorA.Set(0,0);
	revoluteJointDef.localAnchorB.Set(0,0);
	b2RevoluteJoint* joint = (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);
}
void Seesaw::Draw(Bengine::SpriteBatch& spriteBatch)
{
	b2Vec2 position = body->GetPosition();
	b2Vec2 position2 = body2->GetPosition();
	float32 angle = body->GetAngle();
	float32 angle2 = body2->GetAngle();

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/Assignment 4/seesaw.png");
	static Bengine::GLTexture joint = Bengine::ResourceManager::getTexture("Textures/Assignment 4/joint.png");
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	glm::vec4 rectangle = glm::vec4(position.x * CAMERA.x / 32,position.y * CAMERA.y/18,width * CAMERA.x / 32,height * CAMERA.y / 18);
	glm::vec4 rectangle2 = glm::vec4(position2.x * CAMERA.x / 32,position2.y * CAMERA.y/18,height * CAMERA.x / 32,height * CAMERA.y / 18);

	spriteBatch.draw(rectangle, angle, uv, spook.id, 0.0f, color);
	spriteBatch.draw(rectangle2, angle2, uv, joint.id, 0.0f, color);
}

void Seesaw::addForceCenter(float x, float y){
	body->ApplyForceToCenter(b2Vec2(x,y),true);
}