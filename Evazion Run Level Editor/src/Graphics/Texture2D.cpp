#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace GoldSpark {




	Texture2D::Texture2D(const char* image_path)
	{
		this->path = image_path;

		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		CreateImage(image_path);
	}

	Texture2D::~Texture2D()
	{
		
		Free();
	}

	void Texture2D::CreateImage(const char* path)
	{
		//Test image loading
		stbi_set_flip_vertically_on_load(true);
		pixels = stbi_load(path,
			&width,
			&height,
			&channels,
			STBI_rgb_alpha);

		if (pixels == nullptr)
			if (stbi_failure_reason()) {
				std::cout << stbi_failure_reason();
				return;
			}
		

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			GL_NEAREST);

		

		stbi_image_free(pixels);
	}

	

	void Texture2D::Bind()
	{
		
		glBindTexture(GL_TEXTURE_2D, textureID);
		std::cout << glGetError() << std::endl;
	}

	void Texture2D::Bind(int unitNumber)
	{
		glActiveTexture(GL_TEXTURE0 + unitNumber);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
	}

	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Texture2D::Free()
	{
		glDeleteTextures(1, &textureID);
	}

}