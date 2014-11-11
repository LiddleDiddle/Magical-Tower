#pragma once

#include <Box2D\Box2D.h>

#include "GameObject.h"

#include <Bengine\SpriteBatch.h>

#include <Bengine\InputManager.h>

#include <vector>

class GameWorld
{
public:
	GameWorld(void);
	~GameWorld(void);
	
	void CreateBox2DWorld();
	void InitOpenGL(int width, int height);
	void Update(float time, Bengine::InputManager inputManager);
	void Draw ( Bengine::SpriteBatch& spriteBatch );
	void OnKeyEvent();
	void endIt();
	void mouseDown(const b2Vec2& p);
	
private:

	b2World* world;
	std::vector<GameObject*> objects;
	b2Body* m_groundBody;
	bool isMouseDown;
};

class QueryCallback : public b2QueryCallback
{
public:
	QueryCallback(const b2Vec2& point)
	{
		m_point = point;
		m_fixture = NULL;
	}

	bool ReportFixture(b2Fixture* fixture)
	{
		b2Body* body = fixture->GetBody();
		if (body->GetType() == b2_dynamicBody)
		{
			bool inside = fixture->TestPoint(m_point);
			if (inside)
			{
				m_fixture = fixture;

				// We are done, terminate the query.
				return false;
			}
		}

		// Continue the query.
		return true;
	}

	b2Vec2 m_point;
	b2Fixture* m_fixture;
};