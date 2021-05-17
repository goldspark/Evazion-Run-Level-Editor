#pragma once
#include "glm.hpp"
#include "ScriptableObject.h"

namespace GoldFlow {

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag) : Tag(tag){}
	};

	struct TransformComponent {
		glm::mat4 Transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform) : Transform(transform){}
		
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color) : Color(color) {}
	};
	
	struct NativeScriptComponent
	{
		ScriptableObject* Instance = nullptr;

		ScriptableObject* (*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*); // ovo u zagrade znaci 'this'

		template<typename T>
		void Bind() {
			InstantiateScript = [](){return static_cast<ScriptableObject*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };
		}

	};

	

}
