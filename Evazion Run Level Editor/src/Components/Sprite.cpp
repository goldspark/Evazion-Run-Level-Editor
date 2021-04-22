#include "Sprite.h"
#include <iostream>

namespace GoldSpark {



	Sprite::Sprite(const char* texturePath)
	{
		texture = new Texture2D(texturePath);
		this->texturePath = texturePath;
	}

	Sprite::~Sprite()
	{
		std::cout << "Destr";
		Free();
	}

	void Sprite::start()
	{
	}

	void Sprite::update(float dt)
	{
	}

	void Sprite::Free()
	{
		delete texture;
	}

}