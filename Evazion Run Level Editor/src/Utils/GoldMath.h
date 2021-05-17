#pragma once


#include <iostream>
#include <math.h>



namespace GoldSpark {

	namespace Math {

		class Vec2f {
		public:
			float x, y;
		public:
			inline Vec2f() {
				x = 0.0f;
				y = 0.0f;
			}

			inline Vec2f(float x, float y) {
				this->x = x;
				this->y = y;
			}

			~Vec2f() {}


			float Dot(const Vec2f& b);
			Vec2f& Add(const Vec2f& b);
			Vec2f& Sub(const Vec2f& b);
			Vec2f& Mult(const Vec2f& b);
			inline Vec2f& Mult(float s) {
				Vec2f newVec;
				newVec.x = s * this->x;
				newVec.y = s * this->y;
				return newVec;
			}
			void Normalize();

			inline Vec2f operator+(const Vec2f& other) { return Add(other); }
			inline Vec2f operator-(const Vec2f& other) { return Sub(other); }
			inline Vec2f operator*(const Vec2f& other) { return Mult(other); }
			inline Vec2f operator*(const float& s) { return Mult(s); }
			inline Vec2f& operator=(const Vec2f& other) { this->x = other.x; this->y = other.y; return *this;}
			inline bool operator==(const Vec2f& other) { return (x == other.x && y == other.y); }
			
		};

		class Vec3f {
		public:
			float x, y, z;
		public:
			inline Vec3f() {
				x = 0.0f;
				y = 0.0f;
				z = 0.0f;
			}

			inline Vec3f(float x, float y, float z) {
				this->x = x;
				this->y = y;
				this->z = z;
			}

			~Vec3f() {}


			float Dot(const Vec3f& b);
			Vec3f& Add(const Vec3f& b);
			Vec3f& Sub(const Vec3f& b);
			Vec3f& Mult(const Vec3f& b);
			inline Vec3f& Mult(float s) {
				Vec3f newVec;
				newVec.x = s * this->x;
				newVec.y = s * this->y;
				newVec.z = s * this->z;
				return newVec;
			}
			void Normalize();
			Vec3f& Cross(const Vec3f& other);

			inline Vec3f operator+(const Vec3f& other) { return Add(other); }
			inline Vec3f operator-(const Vec3f& other) { return Sub(other); }
			inline Vec3f operator*(const Vec3f& other) { return Mult(other); }
			inline Vec3f operator*(const float& s) { return Mult(s); }
			inline Vec3f& operator=(const Vec3f& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
			inline bool operator==(const Vec3f& other) { return (x == other.x && y == other.y && z == other.z); }
		};



	}

}

std::ostream& operator<<(std::ostream& os, GoldSpark::Math::Vec2f& vec);
std::ostream& operator<<(std::ostream& os, GoldSpark::Math::Vec3f& vec);

