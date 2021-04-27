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
		std::list<GameObject*> gameObjects;
		std::list<GameObject*>::iterator it;
		Renderer2D* renderer2D;
	public:
		
		Scene();
		virtual ~Scene();

		void addToScene(GameObject* gameObject);
		virtual void start();
		virtual void update(float dt, const Vec2f& mouseCoord);
		virtual void Free();

		void RemoveGameObject(int* id);
		inline Renderer2D* GetRenderer() { return renderer2D; }

		inline std::list<GameObject*> &GetGameObjects() { return gameObjects; }
		GameObject* GetGameObject(int index);



	};






}
