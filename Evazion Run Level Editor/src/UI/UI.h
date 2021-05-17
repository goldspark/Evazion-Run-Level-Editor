#pragma once
#include "glad/glad.h"
#include "../GLFW/glfw3.h"
#include "../IMGUI/imgui.h"
#include "../IMGUI/imgui_impl_glfw.h"
#include "../IMGUI/imgui_impl_opengl3.h"


namespace GoldSpark {
	void InitUI(GLFWwindow* window);
	void BegindRenderingUI();
	void UIColorChanger();
	void UIList(const char** itemList, size_t size, int& selection, const char** textureList, size_t sizeT, int& selectionT);
	void UIEditorBox(ImVec2& size, bool& aspectSize, bool& collider);
	void EndRenderingUI(GLFWwindow* window);
	ImVec4& GetBGColor();
}