#include "UI.h"




namespace GoldSpark {

	
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	void InitUI(GLFWwindow* window)
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		const char* glsl_version = "#version 130";

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void BegindRenderingUI()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UIColorChanger()
	{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Backgorund Color");                          // Create a window called "Hello, world!" and append into it.
          // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
			glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);

			ImGui::End();
	}

	void UIList(const char** itemList, size_t size, int& selection, const char** textureList, size_t sizeT, int& selectionT)
	{
		ImGui::Begin("Attributes");
		ImGui::ListBox("CREATE", &selection, itemList, size);
		ImGui::ListBox("Textures", &selectionT, textureList, sizeT);
		ImGui::End();
	}

	void EndRenderingUI(GLFWwindow* window)
	{
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}


	ImVec4& GetBGColor() {
		return clear_color;
	}

}