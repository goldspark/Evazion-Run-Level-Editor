#include <iostream>

#include "glad/glad.h"
#include "glfw3.h"
#include "Application.h"


int main(int argc, char* argv[]) {

	/* Initialize the library */
	if (!glfwInit()) {
		const char* error;
		glfwGetError(&error);
		std::cout << error << std::endl;
		return -1;

	}


	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window = glfwCreateWindow(800, 600, "GoldFlow Game", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		const char* error;
		glfwGetError(&error);
		std::cout << error << std::endl;
		return -1;
	}



	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//Callbacks
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}






	//ENGINE STARTS HERE--------------------------------------------------------------

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	GoldFlow::Application* application = new GoldFlow::Application("Omg");
	application->OnInit();

	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		application->OnUpdate(1.0f);
		


		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	delete application;

	return 0;
}