#include "Collider2D.h"


namespace GoldSpark {

	Collider2D::Collider2D(Vec2f& pos, Vec2f& size)
	{
		name = "Collider2D";
		this->position = pos;
		this->size = size;
	}
	Collider2D::~Collider2D()
	{
		Free();
		
	}

	void Collider2D::start()
	{
		
	}

	void Collider2D::update(float dt)
	{

		
	}

	void Collider2D::Free()
	{

	}

}