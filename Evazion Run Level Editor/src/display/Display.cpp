#include "Display.h"


#include "../Utils/FileCreator.h"
#include "../Graphics/Renderer2D.h"
#include <cstdlib>





/*Controls*/


struct MousePos {
	double xPos, yPos;
};
MousePos mousePos;



/*GLFW CALLBACKS*/
//Callbacks
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	mousePos.xPos = xpos;
	mousePos.yPos = ypos;
}







namespace GoldSpark {


    Display Display::s_Display;
	Renderer2D *renderer;
    


	Display::Display() {



		/* Initialize the library */
		if (!glfwInit()) {
			const char* error;
			glfwGetError(&error);
			std::cout << error << std::endl;
			return;

		}


		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			const char* error;
			glfwGetError(&error);
			std::cout << error << std::endl;
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		//Callbacks
		glfwSetCursorPosCallback(window, cursor_position_callback);


		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize OpenGL context" << std::endl;
			return;
		}


        GoldSpark::InitUI(window);


	
		
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	}
		

    Display& Display::Get() {
        return s_Display;
    }
	






	const float vertices[] = { 0.5f, 0.0f, 0.0f,
						       0.0f, 0.5f, 0.0f,
						      -0.5f, 0.0f, 0.0f };



	void Display::run() {

	
		scene = new EditorScene();
		scene->start();

		float dt = 0.0f;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            BegindRenderingUI();
            UIColorChanger();
            EndRenderingUI(window);
            
			scene->update(dt);
			
           

            glfwSwapBuffers(window);    
            glfwPollEvents();


			//std::cout <<(mousePos.xPos / (WIDTH / 2.0f)) - 1.0f  << ", " << -((mousePos.yPos / (HEIGHT / 2.0f)) - 1.0f) << std::endl;

        }

		ImVec4 v = GetBGColor();
		
		/*
		std::string text;
		text = std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ", " + std::to_string(v.w);
		*/

		//Inputting everything to file

		char s[80];
		sprintf_s(s, "%f, %f, %f, %f", v.x, v.y, v.z, v.w);
		createFile("info.txt", s);

		delete scene;
        glfwTerminate();
       
	}

   


}

