#include "Application.h"


namespace GoldFlow {

	Application::Application(std::string title) : title(title)
	{
		scene = new Scene();
	}

	Application::~Application()
	{
		OnDestroy();
	}

	void Application::OnInit()
	{
		

		
		scene->OnInit();
		

	}

	void Application::OnUpdate(float dt)
	{
		scene->OnUpdate(dt);
	}

	void Application::OnDestroy()
	{
		delete scene;
	}

}