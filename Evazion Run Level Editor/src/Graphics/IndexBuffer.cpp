#include "IndexBuffer.h"





namespace GoldSpark {


	IndexBuffer::IndexBuffer(const GLuint* indices, GLsizeiptr size)
	{
		glCreateBuffers(1, &iboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		Free();
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void IndexBuffer::Free()
	{
		glDeleteBuffers(1, &iboID);
	}


}