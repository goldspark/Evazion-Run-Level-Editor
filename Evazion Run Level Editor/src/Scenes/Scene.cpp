#include "Scene.h"






GoldSpark::Scene::Scene()
{
	renderer2D = new Renderer2D();
}

GoldSpark::Scene::~Scene()
{
	Free();
}

void GoldSpark::Scene::addToScene(GameObject* gameObject)
{
	if (!isRunning)
		gameObjects.push_back(gameObject);
	else {
		gameObjects.push_back(gameObject);
		gameObject->start();
	}
	
}

void GoldSpark::Scene::start()
{
	isRunning = true;
	for (it = gameObjects.begin(); it != gameObjects.end(); it++) {
		(*it)->start();
	}
}

void GoldSpark::Scene::update(float dt)
{	
	for (it = gameObjects.begin();it != gameObjects.end(); it++) {
		(*it)->update(dt);
	}

	renderer2D->Begin();
	for (GameObject* go : gameObjects) {
		renderer2D->DrawQuad(go->position, go->size, go->texture->getTexture());
	}
	renderer2D->Render();
	renderer2D->End();

	

}

void GoldSpark::Scene::Free()
{
	for (GameObject* go : gameObjects)
		delete go;
	delete renderer2D;

	gameObjects.clear();
}

GoldSpark::GameObject* GoldSpark::Scene::GetGameObject(int index)
{
	if (gameObjects.size() > index)
	{
		std::list<GameObject*>::iterator it = std::next(gameObjects.begin(), index);
		return *it;
	}
	else
		return nullptr;
}
