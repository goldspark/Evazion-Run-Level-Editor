#include "Display.h"
#include "../Utils/FileCreator.h"
#include "../Graphics/Renderer2D.h"
#include "../Graphics/DebugDraw.h"
#include "../UI/UI.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <filesystem>




using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;





/*Controls*/


struct MousePos {
	double xPos, yPos;
};
MousePos mousePos;


//Debug drawing
GoldSpark::DebugDraw* debugQuad;

//Display info
static int WIDTH = 640;
static int HEIGHT = 480;

//Texture list info
const char** textureList;
std::string* stextureList;
int numOfTextures = 0;

/*GLFW CALLBACKS*/
//Callbacks

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	GoldState::mouseInfo->x = (xpos / (WIDTH / 2.0f)) - 1.0f;
	GoldState::mouseInfo->y = -((ypos / (HEIGHT / 2.0f)) - 1.0f);
}


void window_size_callback(GLFWwindow* window, int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
		GoldState::deleted = true;
	}
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		GoldState::move = true;
	}
	
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		GoldState::pressed = true;
		GoldState::deleted = false;
		
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);

		mousePos.xPos = xpos;
		mousePos.yPos = ypos;
		

	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		GoldState::deleted = false;
		GoldState::pressed = false;
		GoldState::move = false;
		GoldState::selectedObject = nullptr;
	}
	else if (action == GLFW_RELEASE) {
		GoldState::deleted = false;
		mousePos.xPos = -1;
		mousePos.yPos = -1;
		GoldState::pressed = false;
		GoldState::move = false;
	}
	
}

/*
Imamo jedan sprite kad kliknemo na njega da bude kliknut i cim opet nedje kliknemo
*/



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
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
		glfwSetKeyCallback(window, key_callback);


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
	


	void GoldSpark::Display::DeleteObject() {
		//Delete texture for object for change
		if (GoldState::selectedObject != nullptr) {
			GoldState::selectedObject->texture->Free();
			scene->RemoveGameObject(&GoldState::selectedObject->GetID());
			GoldState::selectedObject = nullptr;
		}
	}


	void LoadTextureFiles() {
		//List all file names
		string path = "assets/";
		//Count number of files
		for (const auto& file : directory_iterator(path)) {
			numOfTextures++;
		}

		textureList = new const char* [numOfTextures];
		stextureList = new string[numOfTextures];
		//Enter file names in texture
		int i = 0;
		for (const auto& file : directory_iterator(path)) {
			stextureList[i] = file.path().string();
			textureList[i] = stextureList[i].c_str();
			i++;
		}
	}

	void Display::run() {

		//List of items to add
		const char* items[] = { "Add Colored Object", "Add Textured Object" };
		int selection = 0;



		//List all file names
		LoadTextureFiles();
		int textureSelection = 0;
		////////////


		debugQuad = new DebugDraw();
	
		scene = new EditorScene();
		scene->start();

		LoadScene("info.emap", *scene);

		float dt = 0.0f;
		Vec2f ndcMousePos(0.0f, 0.0f);

		Vec2f debugQuadPos = { 0.0f, 0.0f };
		Vec3f debugQuadColor = { 0.0f, 1.0f, 0.0f };
		Vec2f debugQuadSize = { 0.2f, 0.2f };

		
		ReadFile("info.emap");

		//Texture2D* test = new Texture2D("assets/building_house_night.png");

        /* Loop until the user closes the window */
		//ID for added game objects
		int id = 0;
		//Check if user should change size whatever he likes as
		bool aspectSize = true;
        while (!glfwWindowShouldClose(window))
        {

            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



			ndcMousePos.x = (mousePos.xPos / (WIDTH / 2.0f)) - 1.0f;
			ndcMousePos.y = -((mousePos.yPos / (HEIGHT / 2.0f)) - 1.0f);
			scene->update(dt, ndcMousePos);

            BegindRenderingUI();
            UIColorChanger();
			UIList(items, 2, selection, textureList, numOfTextures, textureSelection);
			
			if (GoldState::selectedObject != nullptr) {
				ImVec2 size = { GoldState::sizeInfo->x, GoldState::sizeInfo->y };


				

		
				ImGui::Begin("Attributes");
				ImGui::SliderFloat2("SIZE", (float*)&size, 0.0f, 1.0f, "%.3f");
				ImGui::Checkbox("Aspect Size", &aspectSize);
				ImGui::End();

				

			
				if (aspectSize) {
					GoldState::sizeInfo->x = size[0];
					GoldState::sizeInfo->y = GoldState::sizeInfo->x;
				}
				else {
					GoldState::sizeInfo->x = size[0];
					GoldState::sizeInfo->y = size[1];
				}

				
				debugQuadPos.x = GoldState::selectedObject->position.x;
				debugQuadPos.y = GoldState::selectedObject->position.y;


				debugQuadSize.x = GoldState::selectedObject->size.x * 1.001f;
				debugQuadSize.y = GoldState::selectedObject->size.y * 1.001f;

			

				debugQuad->DrawDebugQuad(debugQuadPos, debugQuadSize, debugQuadColor);


			}
			EndRenderingUI(window);
			
			if (GoldState::selectedObject != nullptr && GoldState::deleted)
				DeleteObject();

			//Adding game objects
			if (selection == 1) {
				GameObject* gameObject = new GameObject(id, Vec2f(0.5f, -0.5f), Vec2f(0.2f, 0.2f), *new Texture2D(textureList[textureSelection]));
				scene->addToScene(gameObject);
				selection = 0;
				id++;
			}

            
			
			

			
           

            glfwSwapBuffers(window);    
            glfwWaitEvents();

        }
		

		ImVec4 v = GetBGColor();
		//Inputting everything to file
		char s[80];
		sprintf_s(s, "glClearColor(%f, %f, %f, %f)", v.x, v.y, v.z, v.w);
		createFile("background.txt", s);

		
		
		GoldState::Free();
		delete debugQuad;
		delete [] textureList;
		delete[] stextureList;
		delete scene;
        glfwTerminate();
       
	}

   


}

