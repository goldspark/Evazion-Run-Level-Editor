#include "EditorScene.h"
#include "../Collisions/AABB.h"
#include "../display/State.h"
#include "../Utils/FileCreator.h"
#include "../Components/Collider2D.h"
#include "../IMGUI/imgui.h"
#include "../UI/UI.h"


#include <iostream>






bool aspectSize = false;
bool collider = false;



GoldSpark::EditorScene::EditorScene() : Scene()
{
	debugQuad = new DebugDraw();
	GoldState::debugDraw = debugQuad;
}

GoldSpark::EditorScene::~EditorScene()
{
	Free();
}


void GoldSpark::EditorScene::start(){

	GoldState::selectedObject = nullptr;
}


void GoldSpark::EditorScene::update(float dt, Vec2f& mouseCoord)
{

	

	//Moving collision box
	if (GoldState::moveCollider && GoldState::selectedObject != nullptr) {
		Component* collider = GoldState::selectedObject->GetComponent("Collider");
		if (collider != nullptr) {
			((Collider2D*)collider)->position = *GoldState::mouseInfo - (GoldState::selectedObject->size * 0.5f);
		}

	}

	if (GoldState::selectedObject != nullptr) {

		ImVec2 size = { GoldState::sizeInfo->x, GoldState::sizeInfo->y };

		
		UIEditorBox(size, aspectSize, collider);
		


		if (aspectSize) {
			GoldState::sizeInfo->x = size[0];
			GoldState::sizeInfo->y = GoldState::sizeInfo->x;
		}
		else {
			GoldState::sizeInfo->x = size[0];
			GoldState::sizeInfo->y = size[1];
		}



	}




	if (GoldState::selectedObject == nullptr && GoldState::pressed)
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
			GoldState::selectedObject->position = *GoldState::mouseInfo - (GoldState::selectedObject->size * 0.5f);
		}
	}

	

	Scene::update(dt, mouseCoord);
}

void GoldSpark::EditorScene::Free()
{
	
	SaveScene();
	delete debugQuad;
}

void GoldSpark::EditorScene::SaveScene()
{

	std::string savedData = "\n";
	int id = 0;
	for (GameObject* go : GetGameObjects()) {
		savedData.append("Game object " +std::to_string(id) + ": " + "Position("+ std::to_string(go->position.x) +", " + std::to_string(go->position.y) + ")" + "Size(" + std::to_string(go->size.x) + ", " + std::to_string(go->size.y) + ")"+"Texture(" + go->texture->GetPath() + ")!\n");
		Component* collider = go->GetComponent("Collider");
		if (collider != nullptr) {
			((Collider2D*)collider)->position.x = GoldState::mouseInfo->x;
			((Collider2D*)collider)->position.y = GoldState::mouseInfo->y;
			savedData.append("Collider:\n" + std::to_string(((Collider2D*)collider)->position.x) + "\n" + std::to_string(((Collider2D*)collider)->position.y) + "\n");
		}
		id++;
	}

	createFile("info.emap", savedData.c_str());

	
}
