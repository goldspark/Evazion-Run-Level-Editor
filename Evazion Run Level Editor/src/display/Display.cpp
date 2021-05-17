#include "Display.h"
#include "../Utils/FileCreator.h"
#include "../Graphics/Renderer2D.h"
#include "../UI/UI.h"
#include "../Components/Collider2D.h"
#include "../Graphics/DebugDraw.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <filesystem>




using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;








/*Controls*/


struct MousePressPos {
	double xPos, yPos;
};
MousePressPos mousePressPos;




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
	GoldState::mouseInfo->x = xpos * ((100.0f * GoldState::aspectRatio) / WIDTH);
	GoldState::mouseInfo->y = 100.0f - (ypos * (100.0f / HEIGHT));

	glm::vec4 tempM = glm::vec4{ GoldState::mouseInfo->x, GoldState::mouseInfo->y, 0.0f, 1.0f };

	tempM = glm::translate(glm::mat4(1.0f), glm::vec3{ -1.0f * GoldState::moveCameraLeftRight, 0.0f, 0.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3{ 1.0f, 1.0f, 1.0f }) * tempM;

	GoldState::mouseInfo->x = tempM.x;
	GoldState::mouseInfo->y = tempM.y;
	

}




void window_size_callback(GLFWwindow* window, int width, int height)
{
	WIDTH = width;
	HEIGHT = height;

	
	
	GoldState::camera->RecalculateOrthoCamera(width, height);
	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS) {
		GoldState::deleted = true;
	}
	if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
		GoldState::move = true;
		GoldState::moveCollider = false;
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
		GoldState::moveCollider = true;
		GoldState::move = false;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		GoldState::moveCameraLeftRight -= 5.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		GoldState::moveCameraLeftRight += 5.0f;
	}

	if (key == GLFW_KEY_D && action == GLFW_REPEAT) {
		GoldState::moveCameraLeftRight -= 5.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_REPEAT) {
		GoldState::moveCameraLeftRight += 5.0f;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		GoldState::move = false;
		GoldState::moveCollider = false;
		GoldState::selectedObject = nullptr;
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

		mousePressPos.xPos = xpos;
		mousePressPos.yPos = ypos;
		

	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		GoldState::deleted = false;
		GoldState::pressed = false;
		GoldState::move = false;
		GoldState::moveCollider = false;
		GoldState::selectedObject = nullptr;
	}
	else if (action == GLFW_RELEASE) {
		GoldState::deleted = false;
		mousePressPos.xPos = -1;
		mousePressPos.yPos = -1;
		GoldState::pressed = false;
		GoldState::move = false;
		GoldState::moveCollider = false;
	}
	
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

		GoldState::ptr_window = window;

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
		const char* items[] = { "Add Colored Object(TODO)", "Add Textured Object" };
		int selection = 0;



		//List all file names
		LoadTextureFiles();
		int textureSelection = 0;
		////////////


	
	
		scene = new EditorScene();
		scene->start();

		LoadScene("info.emap", *scene);

		float dt = 0.0f;
		Vec2f ndcMousePos(0.0f, 0.0f);

		GoldState::camera = new Camera(WIDTH, HEIGHT);
		
		ReadFile("info.emap");

		GoldState::debugDrawCollider = new DebugDraw();
		int id = 0;
        while (!glfwWindowShouldClose(window))
        {

            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			
			

			ndcMousePos.x = mousePressPos.xPos * ((100.0f * GoldState::aspectRatio) / WIDTH);
			ndcMousePos.y = 100.0f - (mousePressPos.yPos * (100.0f / HEIGHT));

			glm::vec4 tempM = glm::vec4{ ndcMousePos.x, ndcMousePos.y, 1.0f, 1.0f };

			tempM = glm::translate(glm::mat4(1.0f), glm::vec3{ -1.0f * GoldState::moveCameraLeftRight, 0.0f, 0.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3{ 1.0f, 1.0f, 1.0f }) * tempM;

			ndcMousePos.x = tempM.x;
			ndcMousePos.y = tempM.y;

            BegindRenderingUI();
			scene->update(dt, ndcMousePos);
			//Adding game objects
			if (selection == 1) {
				GameObject* gameObject = new GameObject(id, Vec2f(50.0f, 50.0f), Vec2f(20.0f, 20.0f), *new Texture2D(textureList[textureSelection]));
				scene->addToScene(gameObject);
				selection = 0;
				id++;
			}
            UIColorChanger();
			UIList(items, 2, selection, textureList, numOfTextures, textureSelection);
			EndRenderingUI(window);

		
			if (GoldState::selectedObject != nullptr) {
				glLineWidth(2.0f);
				GoldState::debugDraw->DrawDebugQuad(GoldState::selectedObject->position, GoldState::selectedObject->size, { 0.0f, 1.0f, 0.0f });
				glLineWidth(1.0f);

				Component* collider = GoldState::selectedObject->GetComponent("Collider");
				if (collider != nullptr) {
		

					glLineWidth(2.0f);
					GoldState::debugDrawCollider->DrawDebugQuad(((Collider2D*)collider)->position + GoldState::selectedObject->position, ((Collider2D*)collider)->size, { 1.0f, 0.0f, 0.0f });
					glLineWidth(1.0f);
				}
			}
			

			
			if (GoldState::selectedObject != nullptr && GoldState::deleted)
				DeleteObject();

			

			
           
			glfwPollEvents();
            glfwSwapBuffers(window);    
            

        }
		

		ImVec4 v = GetBGColor();
		char s[80];
		sprintf_s(s, "glClearColor(%f, %f, %f, %f)", v.x, v.y, v.z, v.w);
		createFile("background.txt", s);

		
		
		GoldState::Free();
		delete GoldState::camera;
		delete GoldState::debugDrawCollider;
		delete scene;
		delete [] textureList;
		delete[] stextureList;

	
        glfwTerminate();
       
	}

   


}

