#pragma once
#include "../Math/GoldMath.h"

//Select the platform
#define WINDOWS
//#define ANDROID

#ifdef ANDROID
#include <android/log.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#else WINDOWS
#include <glad/glad.h>
#endif


#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Shader.h"
#include "ShaderCodes.h"
#include "Texture.h"


namespace GoldFlow {

	class Renderer2D {
	private:
		GLuint vao, vbo, ebo;
	public:

		Renderer2D(){}
		~Renderer2D();
		
		void Init();
		void Free();



		void Begin();
		void DrawCube(const glm::vec3 position, const glm::vec2 size, const glm::vec4 color);
		void DrawCubeTextured(const glm::vec3 position, const glm::vec2 size, const Texture& texture, const glm::vec4 TintColor);

		void End();


	};





}