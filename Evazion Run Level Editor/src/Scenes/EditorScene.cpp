#include "EditorScene.h"
#include "../Collisions/AABB.h"
#include "../display/State.h"
#include "../Utils/FileCreator.h"

#include <iostream>










GoldSpark::EditorScene::EditorScene() : Scene()
{
	
}

GoldSpark::EditorScene::~EditorScene()
{
	Free();
}


void GoldSpark::EditorScene::start(){

	GoldState::selectedObject = nullptr;

}


void GoldSpark::EditorScene::update(float dt, const Vec2f& mouseCoord)
{
	if (GoldState::selectedObject == nullptr)
	for(GameObject* go : GetGameObjects())
	if (CheckCollision(mouseCoord, go->size, go->position)) {	
		GoldState::selectedObject = go;
		GoldState::posInfo->x = go->position.x;
		GoldState::posInfo->y = go->position.y;
		GoldState::sizeInfo = &GoldState::selectedObject->size;
	}

	if (GoldState::selectedObject != nullptr)
	{
		if (GoldState::pressed && GoldState::move) {
			GoldState::selectedObject->position = *GoldState::mouseInfo;
		}
	}

	Scene::update(dt, mouseCoord);
}

void GoldSpark::EditorScene::Free()
{
	
	SaveScene();
}

void GoldSpark::EditorScene::SaveScene()
{

	std::string savedData = "\n";
	int id = 0;
	for (GameObject* go : GetGameObjects()) {
		savedData.append("Game object " +std::to_string(id) + ": " + "Position("+ std::to_string(go->position.x) +", " + std::to_string(go->position.y) + ")" + "Size(" + std::to_string(go->size.x) + ", " + std::to_string(go->size.y) + ")"+"Texture(" + go->texture->GetPath() + ")!\n");
		id++;
	}

	createFile("info.emap", savedData.c_str());

	
}
