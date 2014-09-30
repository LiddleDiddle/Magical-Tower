#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Bengine
{

	class Camera2D
	{
	public:
		Camera2D(void);
		~Camera2D(void);

		void init(int screenWidth, int screenHeight);

		void update();

		//setters
		void setPosition(glm::vec2& newPosition) { _position = newPosition;  _needsMatrixUpdate = true; }
		void setScale(glm::float32 newScale) { _scale = newScale;  _needsMatrixUpdate = true; }


		//getters
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }

	private:
		bool _needsMatrixUpdate;
		float _scale;
		int _screenWidth, _screenHeight;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};

}