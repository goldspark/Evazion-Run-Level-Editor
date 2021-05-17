#pragma once
#include "Scene.h"
#include "entt.hpp"

namespace GoldFlow {

	
	class GameObject {
	public:
		GameObject() = default;
		GameObject(entt::entity handle, Scene* scene);
		GameObject(const GameObject& gameObject) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {
			return m_Scene->m_Registry.emplace<T>(m_GameObjectHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_GameObjectHandle);
		}

		template<typename T>
		bool HasComponent()
		{
		
			return m_Scene->m_Registry.any_of<T>(m_GameObjectHandle);
		}

		template<typename T>
		void RemoveComponent() {
			m_Scene->m_Registry.remove<T>(m_GameObjectHandle);
		}


		operator bool() const { return m_GameObjectHandle != entt::null; }

	private:
		entt::entity m_GameObjectHandle{entt::null};
		Scene* m_Scene = nullptr;
	};



}