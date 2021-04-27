#pragma once
#include "../Utils/GoldMath.h"
#include "../Objects/GameObject.h"

//Variables for ImGui editor

namespace GoldState {
extern bool pressed;
extern bool deleted;
extern bool move;
extern GoldSpark::Math::Vec2f* mouseInfo;
extern GoldSpark::Math::Vec2f* posInfo;
extern GoldSpark::Math::Vec2f* sizeInfo;
extern GoldSpark::Math::Vec3f* colorInfo;
extern GoldSpark::GameObject* selectedObject;




	void Free();
}

