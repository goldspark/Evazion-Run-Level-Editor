#pragma once
#include <iostream>
#include <vector>



#include "entt.hpp"
#include "Renderer2D.h"



namespace GoldFlow {

	class GameObject;
	class Scene {
	public:
		std::vector<GameObject*> m_GameObjects;

	public:

		Scene();
		~Scene();

		void OnInit();
		void OnUpdate(float dt);
		void OnDestroy();

		GameObject CreateGameObject(const std::string& name = std::string());

		

	private:
		Renderer2D* renderer;
		entt::registry m_Registry; //Container for Entities and components associated with those entitites
		friend class GameObject;
	};


	

}
