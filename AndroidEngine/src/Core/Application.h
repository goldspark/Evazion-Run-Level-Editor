#pragma once
#include <iostream>
#include <string>
#include "Scene.h"

namespace GoldFlow {


	class Application {
	private:
		Scene* scene;
		std::string title;
	public:
		Application(std::string title);
		~Application();

		void OnInit();
		void OnUpdate(float dt);
		void OnDestroy();


	};








}