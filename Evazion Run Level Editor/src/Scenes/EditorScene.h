#pragma once

#include "Scene.h"


namespace GoldSpark {


	class EditorScene : public Scene {

	public:
		EditorScene();
		

		void start() override;
		void update(float dt) override;
		void Free() override;
	};








}

