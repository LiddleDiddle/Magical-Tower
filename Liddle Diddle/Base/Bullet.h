#pragma once

#include <glm/glm.hpp>
#include <Bengine/SpriteBatch.h>
class Bullet
{
public:
	Bullet(glm::vec2 pos, glm::vec2 dir, float vel, int lifeTime);
	~Bullet(void);

	void draw(Bengine::SpriteBatch& spriteBatch);

	//returns true when dead
	bool update();

private:
	int _lifeTime;
	float _velocity;
	glm::vec2 _direction;
	glm::vec2 _position;
};

