#pragma once
#include "Component.h"
#include "../Graphics/Texture2D.h"



namespace GoldSpark {

	class Sprite : public Component {
	private:
		Texture2D *texture;
		const char* texturePath;
	public:
		Sprite(){}
		Sprite(const char* texturePath);
		~Sprite();

		virtual void start() override;
		virtual void update(float dt) override;
		virtual void Free() override;
		

		inline GLuint& GetTexture() { return texture->getTexture(); }

	};




}