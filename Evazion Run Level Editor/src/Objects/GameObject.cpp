#include "GameObject.h"




GoldSpark::GameObject::GameObject(const Vec2f& position, const Vec2f& size) : position(position), size(size)
{
	this->texture = new Texture2D();
}

GoldSpark::GameObject::GameObject(const Vec2f& position, const Vec2f& size, const Texture2D& texture) : position(position), size(size)
{
	this->texture = new Texture2D(texture);
}

GoldSpark::GameObject::~GameObject()
{
	Free();
	std::cout << "Game Object Free" << std::endl;
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
		c->Free();

	texture->Free();

	
}
