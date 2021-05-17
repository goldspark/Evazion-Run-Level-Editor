#include "AABB.h"


//object1: mouse
bool GoldSpark::CheckCollision(Math::Vec2f& mousePos, const Math::Vec2f& objectSize, const Math::Vec2f& objectPos)
{

	return mousePos.x >= objectPos.x && mousePos.x <= objectPos.x + objectSize.x
		&& mousePos.y >= objectPos.y && mousePos.y <= objectPos.y + objectSize.y;
}
