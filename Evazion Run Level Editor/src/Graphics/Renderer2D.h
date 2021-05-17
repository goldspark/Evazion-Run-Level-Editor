#pragma once
#include "glad/glad.h"
#include "../Objects/GameObject.h"
#include "../Utils/GoldMath.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Shader.h"
#include <list>

/*
-Unos vektora
-Unos normala
-Unos normal mappinga(tangent, bitangent)
-Sve to se batchuje

*/


#define MAX_QUADS     10000
#define MAX_VERTEX    MAX_QUADS * 4
#define MAX_INDEX     MAX_QUADS * 6
#define MAX_TEXTURES  32

using namespace GoldSpark::Math;


namespace GoldSpark {
	


	
	class Renderer2D {
	private:
		VertexArray *m_Vao;
		VertexBuffer *m_Vbo;
		IndexBuffer *m_Ibo;
		Shader* m_Program;
		struct VertexData {
			Vec2f position;
			Vec2f textureCoord;
			float texIndex;
		};
		

	public:
		

		Renderer2D();
		~Renderer2D();

		void Begin();
		void End();
		void Render();
		void Free();
	
		void DrawQuad(const Vec2f& position, const Vec2f& size, const GLuint& texture);
		void ResetTextures();

	public:
		VertexData* bufferData = nullptr;
		VertexData* bufferDataPtr = nullptr;
	
	};


	

}