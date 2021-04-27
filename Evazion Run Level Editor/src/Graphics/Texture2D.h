#pragma once


#include "glad/glad.h"
#include <iostream>
#include <string>






namespace GoldSpark {

	class Texture2D {
	private:
		int width, height, channels;
		GLuint textureID;
		unsigned char* pixels;
		std::string path;
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

		inline const std::string& GetPath() {
			return path; 
		}

		inline GLuint& getTexture() { return textureID; }
	};

}