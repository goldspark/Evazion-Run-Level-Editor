
#include "State.h"


namespace GoldState {
	bool deleted = false;
	bool pressed = false;
	bool move = false;
	GoldSpark::Math::Vec2f* mouseInfo = new GoldSpark::Math::Vec2f();
	GoldSpark::Math::Vec2f* posInfo = new GoldSpark::Math::Vec2f();
	GoldSpark::Math::Vec2f* sizeInfo;
	GoldSpark::Math::Vec3f* colorInfo = new GoldSpark::Math::Vec3f();
	GoldSpark::GameObject* selectedObject = nullptr;




	void Free() {
		delete mouseInfo;
		delete posInfo;
		delete colorInfo;
	}

}

