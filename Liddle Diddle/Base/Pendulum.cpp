#include "Pendulum.h"
#include <Bengine\ResourceManager.h>
#include "MainGame.h"
#include <iostream>

Pendulum::Pendulum(b2World* world, float x, float y)
	: GameObject(world)
{
	CreateBox2dObject(x, y);
}
Pendulum::~Pendulum(void)
{

}

void Pendulum::CreateBox2dObject(float x, float y)
{
	// Circle
	b2CircleShape shape;
	shape.m_radius = .25;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.restitution = 0.7f;
	fd.friction = 0.3f;
	b2BodyDef bd;
	bd.type = b2_staticBody;
	//bd.position.Set(-1.0f , 20.0f);
	bd.position.Set(x, y);
	body = world->CreateBody(&bd);			
	body->CreateFixture(&fd);

	// Circle
	b2CircleShape shape1;
	shape.m_radius = .75;

	b2FixtureDef fd1;
	fd1.shape = &shape;
	fd1.density = 1.0f;
	fd1.restitution = 0.7f;
	fd1.friction = 0.3f;
	b2BodyDef bd1;
	bd1.type = b2_dynamicBody;
	//bd.position.Set(-1.0f , 20.0f);
	bd1.position.Set(x, y-5);
	body2 = world->CreateBody(&bd1);			
	body2->CreateFixture(&fd1);


	b2DistanceJointDef djd;
		djd.bodyA = body;
		djd.bodyB = body2;
		djd.localAnchorA.Set(0.0f, 0.0f);
		djd.localAnchorB.Set(0.0f, 0.0f);
		b2Vec2 d = djd.bodyB->GetWorldPoint(djd.localAnchorB) - djd.bodyA->GetWorldPoint(djd.localAnchorA);
		djd.length = d.Length();
		world->CreateJoint(&djd);


}
void Pendulum::Draw(Bengine::SpriteBatch& spriteBatch)
{
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/Assignment 4/Ball.png");
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;
	
	glm::vec4 rectangle = glm::vec4(position.x * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32,position.y * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32,TheMainGame::Instance()->_camera.getScreenDimensions().x / 32 / 2, TheMainGame::Instance()->_camera.getScreenDimensions().x / 32 / 2);
	spriteBatch.draw(rectangle, angle, uv, spook.id, 0.0f, color);

	position = body2->GetPosition();
	angle = body2->GetAngle();

	rectangle = glm::vec4(position.x * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32,position.y * TheMainGame::Instance()->_camera.getScreenDimensions().x / 32,TheMainGame::Instance()->_camera.getScreenDimensions().x / 32 *1.5, TheMainGame::Instance()->_camera.getScreenDimensions().x / 32 * 1.5);
	spriteBatch.draw(rectangle, angle, uv, spook.id, 0.0f, color);
	
}

void Pendulum::addForceCenter(float x, float y){
	body->ApplyForceToCenter(b2Vec2(x,y),true);
}