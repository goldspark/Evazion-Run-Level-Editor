#include "VertexBuffer.h"
#include <iostream>


namespace GoldSpark {





	VertexBuffer::VertexBuffer(GLsizeiptr size)
	{
		glCreateBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

	}

	VertexBuffer::~VertexBuffer()
	{
		Free();
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
	}

	void VertexBuffer::SetData(const void* data, GLsizeiptr size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);	
	}

	void VertexBuffer::Free()
	{
		glDeleteBuffers(1, &vboID);
	}

}