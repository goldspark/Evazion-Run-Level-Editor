#pragma once


#include "Component.h"


/*
* !FAIL COMPONENT BEING SENT IF THERE IS NO COMPONENT BEING SEARCHED FOR
*/

namespace GoldSpark {

	

	class FailComponent : public Component {
		// Inherited via Component

	public:

		FailComponent() { name = "Fail"; };
		~FailComponent(){}

		virtual void start() override;
		virtual void update(float dt) override;
		virtual void Free() override;
	};



}