#pragma once

//Select the platform
#define WINDOWS
//#define ANDROID

#ifdef ANDROID
#include <android/log.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#define LOG_TAG "DEBUG"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#else WINDOWS
#include <glad/glad.h>
#include <iostream>
#endif



#include <string>

namespace GoldFlow {

	class Texture {
	private:
		GLuint m_TexID;
		std::string m_Path;
	public:
		Texture();
		Texture(std::string path);
		~Texture();

		void Bind();
		void Unbind();

		inline const GLuint& GetID() const { return m_TexID; }
	private:
		void LoadTexture(std::string path);

	};



}