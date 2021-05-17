#include "ParticleSystem.h"

#include "gtc/constants.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/compatibility.hpp"

GoldSpark::ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(1000);
}

void GoldSpark::ParticleSystem::OnUpdate(float dt)
{
	for (Particle& particle : m_ParticlePool) {
		if (!particle.active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.active = false;
			continue;
		}

		particle.LifeRemaining -= dt;
		particle.Position += particle.Velocity * (float)dt;
		particle.Rotation += 0.01f * dt;
	}
}

void GoldSpark::ParticleSystem::OnRender(Camera& camera)
{
	if (!m_QuadVA)
	{
		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		glGenVertexArrays(1, &m_QuadVA);
		glBindVertexArray(m_QuadVA);
	}
}

void GoldSpark::ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	//Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (Random::Float() - 0.5f);
	particle.Velocity.x += particleProps.VelocityVariation.y * (Random::Float() - 0.5f);

	//Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (Random::Float() - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();

}
