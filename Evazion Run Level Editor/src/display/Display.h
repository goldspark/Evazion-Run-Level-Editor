#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include "../UI/UI.h"
#include "../Scenes/EditorScene.h"



#define WIDTH  640
#define HEIGHT  480

namespace GoldSpark {


	class Display {

	public:
		static Display& Get();

	private:
		Display();
		

	public:
		void run();
		~Display() {
			glfwDestroyWindow(window);
			glfwTerminate();
		}


	private:
		GLFWwindow* window;
		static Display s_Display;
		Scene* scene;
	};




}