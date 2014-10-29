#include "Ball.h"
#include <Bengine\ResourceManager.h>

Ball::Ball(b2World* world, float x, float y)
	: GameObject(world)
{
	CreateBox2dObject(x, y);
}
Ball::~Ball(void)
{

}

void Ball::CreateBox2dObject(float x, float y)
{
	// Circle
	b2CircleShape shape;
	shape.m_radius = 0.5f;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.restitution = 0.5f;
	fd.friction = 0.3f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	//bd.position.Set(-1.0f , 20.0f);
	bd.position.Set(x, y);
	body = world->CreateBody(&bd);			
	body->CreateFixture(&fd);

}
void Ball::Draw(Bengine::SpriteBatch& spriteBatch)
{
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/Ball.png");
	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	glm::vec4 rectangle = glm::vec4(position.x * 60,position.y * 60,60,60);
	spriteBatch.draw(rectangle, angle, uv, spook.id, 0.0f, color);
}