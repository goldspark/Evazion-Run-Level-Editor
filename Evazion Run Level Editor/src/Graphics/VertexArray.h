#pragma once
#include <glad/glad.h>

namespace GoldSpark {

	class VertexArray {
	private:
		GLuint vaoID;

	public:
		VertexArray();
		~VertexArray();
		void Bind();
		void Unbind();
		void Free();
	};


}
