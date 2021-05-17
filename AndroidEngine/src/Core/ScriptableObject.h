#pragma once

#include "GameObject.h"


namespace GoldFlow {

	class ScriptableObject {
	public:
		virtual ~ScriptableObject() {}

		template<typename T>
		T& GetComponent()
		{
			return m_GameObject.GetComponent<T>();
		}


	protected:
		virtual void OnCreate() {}
		virtual void OnUpdate(float dt){}
		virtual void OnDestroy(){}


	private:
		GameObject m_GameObject;
		friend class Scene;
	};


}
