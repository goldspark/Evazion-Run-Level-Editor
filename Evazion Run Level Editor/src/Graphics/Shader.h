#pragma once

#include "glad/glad.h"
#include <iostream>
#include <string>


static const char defaultVertexShader[] =
"#version 400 core\n"
"layout(location=0)in vec2 vPosition;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(vPosition, 0.0, 1.0);\n"
"}\n";

static const char defaultFragmentShader[] =
"#version 400 core\n"
"out vec4 color;\n"
"void main(){"
"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";





namespace GoldSpark {


	class Shader {
	private:
		GLuint programID;
	public:
		Shader();
		Shader(const std::string& v, const std::string& f);
		~Shader();


		void Enable();
		void Disable();
		void Free();

		inline GLuint& GetID() { return programID; }
	private:
		GLuint  loadShader(GLenum shaderType, const char* shaderSource);
		GLuint  createProgram(const char* vertexSource, const char* fragmentSource);

	};



}