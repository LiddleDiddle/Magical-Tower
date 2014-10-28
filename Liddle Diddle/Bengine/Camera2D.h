#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Bengine
{
	//camera class for 2d games
	class Camera2D
	{
	public:
		Camera2D(void);
		~Camera2D(void);

		//sets up the orthographic matrix and screen dimensions
		void init(int screenWidth, int screenHeight);

		//updates the camera matrix if needed
		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

		//setters
		void setPosition(glm::vec2& newPosition) { _position = newPosition;  _needsMatrixUpdate = true; }
		void setScale(glm::float32 newScale) { _scale = newScale;  _needsMatrixUpdate = true; }


		//getters
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _cameraMatrix; }
		glm::vec2 getScreenDimensions();

	private:
		bool _needsMatrixUpdate;
		float _scale;
		int _screenWidth, _screenHeight;
		glm::vec2 _position;
		glm::mat4 _cameraMatrix;
		glm::mat4 _orthoMatrix;
	};

}