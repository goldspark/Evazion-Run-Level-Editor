#pragma once
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Utils/GoldMath.h"

/*
* Nacrtaj kocku oko objekta
* Boja kocke zavisi sta je izabrano
* Collision = red
* Selected = green
*/

namespace GoldSpark {

	struct VertexData {
		GoldSpark::Math::Vec2f position;
		GoldSpark::Math::Vec3f color;
	};

	class DebugDraw {
	private:
		VertexArray* vao;
		VertexBuffer* vbo;
		IndexBuffer* ibo;
		Shader* shader;
	public:
		DebugDraw();
		~DebugDraw();

		void DrawDebugQuad(const Math::Vec2f& pos, const Math::Vec2f& size, const Math::Vec3f& color);
		
	};
}