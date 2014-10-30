#include "Box.h"
#include <Bengine\ResourceManager.h>

Box::Box(b2World* world, float x, float y)
	:GameObject(world)
{
	CreateBox2dObject(x, y);
}

Box::~Box(void)
{

}

void Box::CreateBox2dObject(float x, float y)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(x, y);
	bodyDef.angularVelocity = 0.3f;

	b2Vec2 v(0, 1.0f);

	body = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(0.5f, 0.5f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	fixtureDef.friction = 1.0f;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.5f;

	body->CreateFixture(&fixtureDef);
}
void Box::Draw(Bengine::SpriteBatch& spriteBatch)
{
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/Box.png");
	Bengine::Color color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	glm::vec4 rectangle = glm::vec4(position.x * 60,position.y * 60,60,60);

	spriteBatch.draw(rectangle, angle, uv, spook.id, 0.0f, color);
}
