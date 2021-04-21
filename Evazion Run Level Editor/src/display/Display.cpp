#include "Display.h"

#include "../Utils/GoldMath.h"
#include "../Graphics/VertexBuffer.h"
#include "../Graphics/Shader.h"
#include "../Utils/FileCreator.h"

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



		Math::Vec2f first(1.0f, 2.0f);
		Math::Vec2f second(1.0f, 1.0f);

		std::cout << first << std::endl;
		std::cout << second << std::endl;

		first.Normalize();
		
		std::cout << first << std::endl;


	}
		

    Display& Display::Get() {
        return s_Display;
    }
	






	const float vertices[] = { 0.5f, 0.0f, 0.0f,
						       0.0f, 0.5f, 0.0f,
						      -0.5f, 0.0f, 0.0f };

	Shader* defaultShader;

	void Display::run() {

		defaultShader = new Shader();

		VertexArray* vao = new VertexArray();
		vao->Bind();
		VertexBuffer* vbo = new VertexBuffer(sizeof(vertices));
		vbo->SetData(vertices, sizeof(vertices));
		vao->Unbind();

		
		

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {

            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			defaultShader->Enable();
			vao->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
			defaultShader->Disable();

            BegindRenderingUI();
            UIColorChanger();
            EndRenderingUI(window);
            
           
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

		delete defaultShader;
        delete vao;
        delete vbo;
        glfwTerminate();
       
	}

   


}

