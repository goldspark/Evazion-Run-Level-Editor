#pragma once

#include "../Utils/GoldMath.h"
#include "../Graphics/Texture2D.h"
#include "../Components/Component.h"
#include <list>



namespace GoldSpark {
	using namespace Math;


	class Component;

	

	class GameObject {
	private:
		std::list<Component*> components;
		int id;
	public:
		GameObject(int& id, const Vec2f& position, const Vec2f& size);
		GameObject(int& id, const Vec2f& position, const Vec2f& size, const Texture2D& texture);
		~GameObject();

		void AddComponent(Component& c);

		void start();
		void update(float dt);
		void Free();

		Component* GetComponent(const char* name);

		void SetID(int id) { this->id = id; }
		int& GetID()  { return id; }

	public:
		Vec2f position;
		Vec2f size;
		Texture2D *texture;
	};



}