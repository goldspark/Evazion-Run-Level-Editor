#pragma once
#include "glad/glad.h"



namespace GoldSpark {




	class IndexBuffer {
	private:
		GLuint iboID;

	public:
		IndexBuffer(const GLuint* indices, GLsizeiptr ptr);
		~IndexBuffer();

		void Bind();
		void Unbind();
		void Free();
	};





}

