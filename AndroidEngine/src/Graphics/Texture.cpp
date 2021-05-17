#include "Texture.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif


#include <stb_image.h>


namespace GoldFlow {

	Texture::Texture()
	{

	}

	Texture::Texture(std::string path)
	{
		LoadTexture(path);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TexID);
	}

	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_TexID);
	}

	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::LoadTexture(std::string path)
	{

		int width, height, channels;
		//Test image loading
		stbi_set_flip_vertically_on_load(true);
		stbi_uc *pixels = stbi_load(path.c_str(),
			&width,
			&height,
			&channels,
			STBI_rgb_alpha);

		if (pixels == nullptr)
			if (stbi_failure_reason()) {
				#ifdef WINDOWS
				std::cout << stbi_failure_reason();
				#else
				LOGD("%s", stbi_failure_reason());
				#endif
				return;
			}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TexID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		//glGenerateMipmap(GL_TEXTURE_2D); FOR 2D IT IS NOT NEEDED!!

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			GL_NEAREST);


		stbi_image_free(pixels);
	}







}
