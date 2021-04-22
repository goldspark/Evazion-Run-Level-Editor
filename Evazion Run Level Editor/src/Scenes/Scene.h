#pragma once
#include "../Objects/GameObject.h"
#include "../Graphics/Texture2D.h"
#include "../Graphics/Renderer2D.h"
#include <iostream>
#include <list>


namespace GoldSpark {


	class Scene {
	private:
		bool isRunning = false;
		Renderer2D *renderer2D;
		std::list<GameObject*> gameObjects;
		std::list<GameObject*>::iterator it;
	public:
		Scene();
		~Scene();

		void addToScene(GameObject* gameObject);
		virtual void start();
		virtual void update(float dt);
		virtual void Free();

		GameObject* GetGameObject(int index);

	};






}
