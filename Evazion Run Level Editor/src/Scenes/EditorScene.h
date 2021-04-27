#pragma once

#include "Scene.h"


namespace GoldSpark {


	class EditorScene : public Scene {

	public:
		EditorScene();
		~EditorScene() override;

		void start() override;
		void update(float dt, const Vec2f& mouseCoord) override;
		void Free() override;

		void SaveScene();
	};



	




}

