#pragma once
#include "../Objects/GameObject.h"

namespace GoldSpark {

	class GameObject;

	class Component {
	public:
		GameObject* gameObject;
	public:
		
		virtual void start() = 0;
		virtual void update(float dt) = 0;
		virtual void Free() = 0;
	};


}
