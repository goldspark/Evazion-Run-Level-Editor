#include "GameObject.h"
#include "../Components/FailComponent.h"



GoldSpark::GameObject::GameObject(int& id, const Vec2f& position, const Vec2f& size) :id(id), position(position), size(size)
{
	this->texture = new Texture2D();
}

GoldSpark::GameObject::GameObject(int& id, const Vec2f& position, const Vec2f& size, const Texture2D& texture) :id(id), position(position), size(size)
{
	this->texture = new Texture2D(texture);
}

GoldSpark::GameObject::~GameObject()
{
	Free();
}

void GoldSpark::GameObject::AddComponent(Component& c)
{
	c.gameObject = this;
	components.push_back(&c);
}

void GoldSpark::GameObject::start()
{
	for (Component* c : components) {
		c->start();
	}
}

void GoldSpark::GameObject::update(float dt)
{
	
	for (Component* c : components) {
		c->update(dt);
	}
}

void GoldSpark::GameObject::Free()
{

	for (Component* c : components)
		delete c;

	delete texture;
	
}

GoldSpark::Component* GoldSpark::GameObject::GetComponent(const char* name)
{
	for (Component* c : components) {
		if (strcmp(name, c->name)) {
			return c;
		}
	}

	return nullptr;
}
