#include "Bullet.h"
#include <Bengine/ResourceManager.h>

Bullet::Bullet(glm::vec2 pos, glm::vec2 dir, float vel, int lifeTime)
{
	_position = pos;
	_direction = dir;
	_velocity = vel;
	_lifeTime = lifeTime;
}


Bullet::~Bullet(void)
{
}

void Bullet::draw(Bengine::SpriteBatch& spriteBatch){
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static Bengine::GLTexture spook = Bengine::ResourceManager::getTexture("Textures/PS4_Circle.png");
	Bengine::ColorRGBA8 color;
	color.r = 255;
    color.g = 255;
    color.b = 255;
    color.a = 255;

	glm::vec4 rectangle = glm::vec4(_position.x,_position.y,100,100);

	spriteBatch.draw(rectangle, 0, uv, spook.id, 0.0f, color);
}

bool Bullet::update(){
	_position += _direction * _velocity;
	_lifeTime--;
	if(_lifeTime == 0){
		return true;
	}
	return false;
}