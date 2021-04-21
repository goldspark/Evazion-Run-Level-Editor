#pragma once

#include "VertexArray.h"



namespace GoldSpark {

	class VertexBuffer {
	private:
		GLuint vboID;

	public:
		VertexBuffer(GLsizeiptr size);
		~VertexBuffer();

		void Bind();
		void Unbind();
		void SetData(const void* data, GLsizeiptr size);
		void Free();
	
	};





}

