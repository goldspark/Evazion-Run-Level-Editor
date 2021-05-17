#include "Scene.h"
#include "glm.hpp"

#include "Components.h"
#include "GameObject.h"
namespace GoldFlow {

	

	Scene::Scene() {
		renderer = new Renderer2D();
	}


	Scene::~Scene() {
		OnDestroy();
	}

	void Scene::OnInit()
	{
		GameObject *square, *square2;
		square = &CreateGameObject("Square");
		square2 = &CreateGameObject("Square2");
		
		class TagController : public ScriptableObject {
		public:

			void OnCreate(){
				std::cout << "Created!!" << std::endl;
			}

			void OnDestroy(){

			}

			void OnUpdate(float dt) {

			}
			
		};
		
		square2->AddComponent<NativeScriptComponent>().Bind<TagController>();
	}

	void Scene::OnUpdate(float dt)
	{

		
	    //Update scripts
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				if (!nsc.Instance) {
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_GameObject = GameObject{ entity, this };
					nsc.Instance->OnCreate();
				}

		});
		
		
		renderer->Begin();
		renderer->DrawCube({ 0.0f, 0.0f, 0.0f }, { 0.5f, 0.5f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		renderer->End();
		
	}

	void Scene::OnDestroy()
	{
		for (GameObject* go : m_GameObjects) {
			delete go;
		}
		m_Registry.clear();

		delete renderer;
	}

	GameObject Scene::CreateGameObject(const std::string& name)
	{
		GameObject gameObject =  { m_Registry.create(), this };
		gameObject.AddComponent<TransformComponent>();
		auto& tag = gameObject.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "GameObject" : name;

		m_GameObjects.push_back(new GameObject(gameObject));

		return gameObject;
	}




}