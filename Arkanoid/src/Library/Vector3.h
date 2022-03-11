#pragma once

#include <cmath>

struct Vector3
{
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3 VectorAbs(Vector3 v)
	{
		return {
			std::abs(v.x),
			std::abs(v.y),
			std::abs(v.z)
		};
	}

	Vector3 operator+(Vector3 right)
	{
		return {
			this->x + right.x,
			this->y + right.y,
			this->z + right.z
		};
	}

	Vector3 operator-(Vector3 right)
	{
		return {
			this->x - right.x,
			this->y - right.y,
			this->z - right.z
		};
	}

	Vector3& operator+=(Vector3 right)
	{
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;

		return *this;
	}

	Vector3& operator*(float scalar)
	{
		Vector3 vec = *this;

		vec.x *= scalar;
		vec.y *= scalar;
		vec.z *= scalar;

		return vec;
	}

	friend Vector3& operator* (float scalar, Vector3 vec)
	{
		vec.x *= scalar;
		vec.y *= scalar;
		vec.z *= scalar;

		return vec;
	}

	Vector3 operator*(int scalar)
	{
		Vector3 vec = *this;

		vec.x *= scalar;
		vec.y *= scalar;
		vec.z *= scalar;

		return vec;
	}

	float VectorDot(Vector3 left, Vector3 right)
	{
		return (left.x * right.x + left.y * right.y + left.z * right.z);
	}

	float VectorLength(Vector3 vec)
	{
		return std::sqrt(VectorDot(vec, vec));
	}

	float VectorDistance(Vector3 left, Vector3 right)
	{
		Vector3 distVec = left - right;

		return VectorLength(distVec);
	}

	Vector3& Normalize()
	{
		float magnitude = VectorLength(*this);

		this->x *= (1.0f / magnitude);
		this->y *= (1.0f / magnitude);
		this->z *= (1.0f / magnitude);

		return *this;
	}

	Vector3 Normalized()
	{
		float magnitude = VectorLength(*this);
		Vector3 vec = *this;

		vec.x *= (1.0f / magnitude);
		vec.y *= (1.0f / magnitude);
		vec.z *= (1.0f / magnitude);

		return vec;
	}

	float DotNormalized(Vector3 left, Vector3 right)
	{
		return (left.x * right.x + left.y * right.y + left.z * right.z);
	}

	Vector3& RotateDegrees2D(float angle)
	{
		angle *= M_PI / 180.0f;

		this->x = this->x * cos(angle) - this->y * sin(angle);
		this->y = this->x * sin(angle) + this->y * cos(angle);

		return *this;
	}

	Vector3& SetAngle(float angle)
	{
		angle *= M_PI / 180.0f;

		float vecLength = VectorLength(*this);

		this->x = (vecLength)*cos(angle);
		this->y = (vecLength)*sin(angle);

		return *this;
	}

};
