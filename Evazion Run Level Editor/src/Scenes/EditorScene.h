#pragma once

#include "Scene.h"
#include "../Graphics/DebugDraw.h"


namespace GoldSpark {


	class EditorScene : public Scene {
	private:
		DebugDraw* debugQuad;

	public:
		EditorScene();
		~EditorScene() override;

		void start() override;
		void update(float dt, Vec2f& mouseCoord) override;
		void Free() override;

		void SaveScene();
	};



	




}

