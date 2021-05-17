#pragma once
#include "Component.h"
#include "../Graphics/DebugDraw.h"

namespace GoldSpark {



	class Collider2D : public Component {
	public:

		Collider2D(Vec2f& pos, Vec2f& size);
		~Collider2D();

		// Inherited via Component
		virtual void start() override;

		virtual void update(float dt) override;

		virtual void Free() override;

	public:
		Vec2f position;
		Vec2f size;

	};




}