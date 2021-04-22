#pragma once


#include "glad/glad.h"
#include <iostream>






namespace GoldSpark {

	class Texture2D {
	private:
		int width, height, channels;
		GLuint textureID;
		unsigned char* pixels;
	private:
		void CreateImage(const char* path);

	public:
		Texture2D(){}
		Texture2D(const char* image_path);
		~Texture2D();

		void Bind(int unitNumber);
		void Bind();
		void Unbind();
		void Free();

		inline GLuint& getTexture() { return textureID; }
	};

}