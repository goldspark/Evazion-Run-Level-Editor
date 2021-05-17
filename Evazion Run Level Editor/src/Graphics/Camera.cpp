#include "Camera.h"
#include "../display/State.h"

namespace GoldSpark {

	Camera::Camera(int width, int height)
	{
		
		m_OrthoMatrix = glm::mat4(1.0f);
		RecalculateOrthoCamera(width, height);
	}

	void Camera::RecalculateOrthoCamera(int width, int height)
	{
		GoldState::aspectRatio = m_AspectRatio = 19.0f / 9.0f;
		float orthoLeft = 0.0f;  
		float orthoRight = 100.0f * m_AspectRatio;
		float orthoUp = 100.0f;
		float orthoDown = 0.0f;
		m_OrthoMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp);

		

		int aspectWidth = width;
		int aspectHeight = (int)((float)aspectWidth / m_AspectRatio);
		if (aspectHeight > height)
		{
			aspectHeight = height;
			aspectWidth = (int)((float)aspectHeight * m_AspectRatio);
		}

		int vpX = (int)(((float)width / 2.0f) - ((float)aspectWidth / 2.0f));
		int vpY = (int)(((float)height / 2.0f) - ((float)aspectHeight / 2.0f));

		GoldState::screenInfo.x = aspectWidth;
		GoldState::screenInfo.y = aspectHeight;

		glViewport(vpX, vpY, aspectWidth, aspectHeight);
	}

	Camera::~Camera()
	{

	}

}
