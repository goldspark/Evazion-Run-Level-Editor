#include "EditorScene.h"
#include <iostream>



GoldSpark::GameObject* cube;
GoldSpark::Texture2D* texture;
GoldSpark::Sprite *sprite;

GoldSpark::EditorScene::EditorScene() : Scene()
{
	
}



void GoldSpark::EditorScene::start(){
	sprite = new Sprite("assets/building_shop_day.png");
    texture = new Texture2D("assets/building_shop_day.png");
	cube = new GameObject(Vec2f(0.0f, 0.0f), Vec2f(0.5f, 0.5f), *texture);
	cube->AddComponent(*sprite);
	addToScene(cube);
}

void GoldSpark::EditorScene::update(float dt)
{
	cube->update(dt);

	Scene::update(dt);
}

void GoldSpark::EditorScene::Free()
{
	cube->Free();
	delete texture;
}
