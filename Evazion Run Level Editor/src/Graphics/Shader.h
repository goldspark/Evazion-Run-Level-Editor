#pragma once

#include "glad/glad.h"
#include <iostream>


namespace GoldSpark {


	class Shader {
	private:
		GLuint programID;
	public:
		Shader();
		Shader(const char* v, const char* f);
		~Shader();


		void Enable();
		void Disable();
		void Free();
	private:
		GLuint  loadShader(GLenum shaderType, const char* shaderSource);
		GLuint  createProgram(const char* vertexSource, const char* fragmentSource);

	};



}