#include "Renderer2D.h"


#define BATCH_SIZE 1000

namespace GoldFlow {

	struct VertexData {
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 Texture;
		float Index;
	};
	VertexData* vertexBase;
	VertexData* vertexBasePtr;

	int textureSlots[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int currentTextureSlot = 1;
	int indicesCount = 0;

	Shader *shader;


	Renderer2D::~Renderer2D()
	{
		Free();
	}

	void Renderer2D::Init() {

		shader = new Shader("Textured Shader", vertexShader, fragmentShader);
		vertexBase = new VertexData[BATCH_SIZE * 11];




		//Generate indices for each item

		GLushort indices[BATCH_SIZE * 6];

		int offset = 0;
		for (int i = 0; i < BATCH_SIZE * 6; i += 6)
		{
			indices[i] = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;
			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset;

			offset += 4;
		}


		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, BATCH_SIZE * 11, nullptr, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, BATCH_SIZE * 6, indices, GL_STATIC_DRAW);


		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, Position));
		glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, Color));
		glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, Texture));
		glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, Index));


		int32_t samplers[8];
		for (uint32_t i = 0; i < 8; i++)
		{
			samplers[i] = i;
		}

		shader->Bind();
		shader->SetIntArray("u_Texture", samplers, 8);

	}


	void Renderer2D::Free() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
		glDeleteBuffers(1, &ebo);
		delete shader;
		delete vertexBase;
	}



	void Renderer2D::Begin() {
	
		vertexBasePtr = vertexBase;

		currentTextureSlot = 1;
		indicesCount = 0;
	}

	void Renderer2D::DrawCube(const glm::vec3 position, const glm::vec2 size, const glm::vec4 color) {

		if (indicesCount > (BATCH_SIZE * 6) - 6)
		{
			End();
			Begin();
		}

		vertexBasePtr->Position = position;
		vertexBasePtr->Color = color;
		vertexBasePtr->Texture = { 0.0f, 0.0f };
		vertexBasePtr->Index = 0.0f;
		vertexBasePtr++;

		vertexBasePtr->Position = {position.x + size.x, position.y, position.z};
		vertexBasePtr->Color = color;
		vertexBasePtr->Texture = { 0.0f, 0.0f };
		vertexBasePtr->Index = 0.0f;
		vertexBasePtr++;

		vertexBasePtr->Position = { position.x + size.x, position.y + size.y, position.z };
		vertexBasePtr->Color = color;
		vertexBasePtr->Texture = { 0.0f, 0.0f };
		vertexBasePtr->Index = 0.0f;
		vertexBasePtr++;

		vertexBasePtr->Position = { position.x, position.y + size.y, position.z };
		vertexBasePtr->Color = color;
		vertexBasePtr->Texture = { 0.0f, 0.0f };
		vertexBasePtr->Index = 0.0f;
		vertexBasePtr++;


		indicesCount += 6;
	}

	void Renderer2D::DrawCubeTextured(const glm::vec3 position, const glm::vec2 size, const Texture& texture, const glm::vec4 TintColor) {

		if (indicesCount > (BATCH_SIZE * 6) - 6 || currentTextureSlot > 8)
		{
			Begin();
			End();
		}


		float cIndex = 0.0f;
		for (int i = 1; i < currentTextureSlot; i++)
		{
			if (texture.GetID() == textureSlots[i])
			{
				cIndex = (float)i;
			}
		}

		if (cIndex == 0)
		{
			cIndex = currentTextureSlot;
			textureSlots[currentTextureSlot] = texture.GetID();
			currentTextureSlot++;
		}


		vertexBasePtr->Position = position;
		vertexBasePtr->Color = {1.0f, 1.0f, 1.0f, 1.0f};
		vertexBasePtr->Texture = { 0.0f, 0.0f };
		vertexBasePtr->Index = cIndex;
		vertexBasePtr++;

		vertexBasePtr->Position = { position.x + size.x, position.y, position.z };
		vertexBasePtr->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		vertexBasePtr->Texture = { 1.0f, 0.0f };
		vertexBasePtr->Index = cIndex;
		vertexBasePtr++;

		vertexBasePtr->Position = { position.x + size.x, position.y + size.y, position.z };
		vertexBasePtr->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		vertexBasePtr->Texture = { 1.0f, 1.0f };
		vertexBasePtr->Index = cIndex;
		vertexBasePtr++;

		vertexBasePtr->Position = { position.x, position.y + size.y, position.z };
		vertexBasePtr->Color = { 1.0f, 1.0f, 1.0f, 1.0f };
		vertexBasePtr->Texture = { 0.0f, 1.0f };
		vertexBasePtr->Index = cIndex;
		vertexBasePtr++;

		indicesCount += 6;
	}

	void Renderer2D::End() {


		//Putting data in a buffer
		GLsizeiptr size = (uint8_t*)vertexBasePtr - (uint8_t*)vertexBase;
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertexBase);

		//Displaying the rendering data
		for (int i = 0; i < currentTextureSlot; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
		}

		shader->Bind();
		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_SHORT, nullptr);

		
		shader->Unbind();

	}






}