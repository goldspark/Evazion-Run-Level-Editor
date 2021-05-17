#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace GoldSpark {

	class Camera {
	private:
		glm::mat4 m_OrthoMatrix;
		float m_AspectRatio;
	public:
		Camera(int width, int height);
		~Camera();
		void RecalculateOrthoCamera(int width, int height);
		inline float& GetAspectRatio() { return m_AspectRatio; }
		glm::mat4& GetCameraMatrix() { return m_OrthoMatrix; }
	
	};

}