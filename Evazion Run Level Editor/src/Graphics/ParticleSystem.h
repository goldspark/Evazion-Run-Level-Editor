#pragma once
#include "glad/glad.h"
#include "glm.hpp"
#include "Camera.h"
#include "../Utils/Random.h"
#include "../Graphics/Shader.h"
#include <vector>
#include <memory>



namespace GoldSpark {


	struct ParticleProps
	{
		glm::vec2 Position;
		glm::vec2 Velocity, VelocityVariation;
		glm::vec4 ColorBegin, ColorEnd;
		float SizeBegin, SizeEnd, SizeVariation;
		float LifeTime = 1.0f;
	};


	class ParticleSystem {
	public:
		ParticleSystem();

		void OnUpdate(float dt);
		void OnRender(Camera& camera);

		void Emit(const ParticleProps& particleProps);
	private:
		struct Particle
		{
			glm::vec2 Position;
			glm::vec2 Velocity;
			glm::vec4 ColorBegin, ColorEnd;
			float Rotation = 0.0f;
			float SizeBegin, SizeEnd;

			float LifeTime = 1.0f;
			float LifeRemaining = 0.0f;
			bool active = false;
		};

		std::vector<Particle> m_ParticlePool;
		uint32_t m_PoolIndex = 999;

		GLuint m_QuadVA = 0;
		std::unique_ptr<Shader> m_ParticleShader;
		GLuint m_ParticleShaderViewProj, m_ParticleShaderTransform, m_ParticleShaderColor;
	};











}