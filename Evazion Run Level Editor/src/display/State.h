#pragma once
#include "../Utils/GoldMath.h"
#include "../Objects/GameObject.h"
#include "../Graphics/DebugDraw.h"
#include "../Graphics/Camera.h"
#include "glfw3.h"


//Variables for ImGui editor

namespace GoldState {
extern bool pressed;
extern bool deleted;
extern bool move;
extern bool moveCollider;
extern GoldSpark::Camera* camera;
extern GoldSpark::Math::Vec2f* mouseInfo;
extern GoldSpark::Math::Vec2f* posInfo;
extern GoldSpark::Math::Vec2f* sizeInfo;
extern GoldSpark::Math::Vec3f* colorInfo;
extern GoldSpark::GameObject* selectedObject;
extern bool mousePressed;
extern GLFWwindow* ptr_window;
extern GoldSpark::DebugDraw* debugDraw;
extern GoldSpark::DebugDraw* debugDrawCollider;
extern float aspectRatio;
extern float moveCameraLeftRight;
extern glm::vec2 screenInfo;




	void Free();
}

