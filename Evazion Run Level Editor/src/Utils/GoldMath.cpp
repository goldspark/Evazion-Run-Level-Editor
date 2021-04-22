#include "GoldMath.h"

using namespace GoldSpark::Math;





float Vec2f::Dot(const Vec2f& b)
{
	return this->x * b.x + this->y * b.y;
}

Vec2f& Vec2f::Add(const Vec2f& b)
{
	Vec2f  newVec;
	newVec.x = this->x + b.x;
	newVec.y = this->y + b.y;
	return newVec;
}

Vec2f& Vec2f::Sub(const Vec2f& b)
{
	Vec2f  newVec;
	newVec.x = this->x - b.x;
	newVec.y = this->y - b.y;
	return newVec;
}

Vec2f& Vec2f::Mult(const Vec2f& b)
{
	Vec2f  newVec;
	newVec.x = this->x * b.x;
	newVec.y = this->y * b.y;
	return newVec;
}

void Vec2f::Normalize()
{
	float magnitude = sqrt(this->x * this->x + this->y * this->y);
	this->x = (this->x / magnitude);
	this->y = (this->y / magnitude);
}







float GoldSpark::Math::Vec3f::Dot(const Vec3f& b)
{
	return this->x * b.x + this->y * b.y + this->z * b.z;
}

Vec3f& GoldSpark::Math::Vec3f::Add(const Vec3f& b)
{
	Vec3f  newVec;
	newVec.x = this->x + b.x;
	newVec.y = this->y + b.y;
	newVec.z = this->z + b.z;
	return newVec;
}

Vec3f& GoldSpark::Math::Vec3f::Sub(const Vec3f& b)
{
	Vec3f  newVec;
	newVec.x = this->x - b.x;
	newVec.y = this->y - b.y;
	newVec.z = this->z - b.z;
	return newVec;
}

Vec3f& GoldSpark::Math::Vec3f::Mult(const Vec3f& b)
{
	Vec3f  newVec;
	newVec.x = this->x * b.x;
	newVec.y = this->y * b.y;
	newVec.z = this->z * b.z;
	return newVec;
}

void GoldSpark::Math::Vec3f::Normalize()
{
	float magnitude = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	this->x = (this->x / magnitude);
	this->y = (this->y / magnitude);
	this->z = (this->z / magnitude);
}

Vec3f& GoldSpark::Math::Vec3f::Cross(const Vec3f& other)
{
	Vec3f vec3(1.0f, 1.0f, 1.0f);
	return vec3;
}




std::ostream& operator<<(std::ostream& os, Vec2f& vec) {
	os << "(" << vec.x << "," << vec.y << ")"; return os;
	return os;
}

std::ostream& operator<<(std::ostream& os, Vec3f& vec) {
	os << "(" << vec.x << "," << vec.y <<  "," << vec.z << ")"; return os;
	return os;
}