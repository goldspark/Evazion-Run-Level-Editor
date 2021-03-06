#pragma once
#include <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include "../Scenes/EditorScene.h"
#include "State.h"
#include "../Utils/FileReader.h"





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

		void DeleteObject();

	private:
		GLFWwindow* window;
		static Display s_Display;
		Scene* scene;
	};




}