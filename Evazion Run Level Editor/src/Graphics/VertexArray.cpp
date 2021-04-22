#include "VertexArray.h"
#include <iostream>



namespace GoldSpark {


	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &vaoID);
	}

	VertexArray::~VertexArray()
	{
		Free();
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(vaoID);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::Free()
	{
		glDeleteVertexArrays(1, &vaoID);
	}

}