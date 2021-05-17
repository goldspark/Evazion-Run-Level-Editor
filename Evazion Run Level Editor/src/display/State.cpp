
#include "State.h"


namespace GoldState {
	bool deleted = false;
	bool pressed = false;
	bool move = false;
	bool moveCollider = false;
	GoldSpark::Math::Vec2f* mouseInfo = new GoldSpark::Math::Vec2f();
	GoldSpark::Math::Vec2f* posInfo = new GoldSpark::Math::Vec2f();
	GoldSpark::Math::Vec2f* sizeInfo;
	GoldSpark::Math::Vec3f* colorInfo = new GoldSpark::Math::Vec3f();
	GoldSpark::GameObject* selectedObject = nullptr;
	GLFWwindow* ptr_window = nullptr;
	GoldSpark::DebugDraw* debugDraw = nullptr;
	GoldSpark::DebugDraw* debugDrawCollider = nullptr;
	GoldSpark::Camera* camera = nullptr;

	float aspectRatio = 0.0f;
	float moveCameraLeftRight = 0.0f;
	glm::vec2 screenInfo = glm::vec2{ 0.0f, 0.0f };

	void Free() {
		delete mouseInfo;
		delete posInfo;
		delete colorInfo;
	}

}

