#pragma once
#include <cmath>

#pragma warning(disable:26495)
class Vector3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float X;
			float Y;
			float Z;
		};
	};

	Vector3() : x(0), y(0), z(0) {}
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(float value) : x(value), y(value), z(value) {}
	Vector3(const Vector3& vec) : x(vec.x), y(vec.y), z(vec.z) {}

	bool operator!=(const Vector3& right) const { return x != right.x || y != right.y || z != right.z; }
	bool operator==(const Vector3& right) const { return !(*this != right); }

	Vector3 operator+(const Vector3& right) const { return Vector3(x + right.x, y + right.y, z + right.z); }
	Vector3 operator-(const Vector3& right) const { return Vector3(x - right.x, y - right.y, z - right.z); }
	Vector3 operator*(const Vector3& right) const { return Vector3(x * right.x, y * right.y, z * right.z); }
	Vector3 operator/(const Vector3& right) const { return Vector3(x / right.x, y / right.y, z / right.z); }
	Vector3& operator=(const Vector3& right) { x = right.x; y = right.y; z = right.z; return *this; }
	Vector3& operator+=(const Vector3& right) { x += right.x; y += right.y; z += right.z; return *this; }
	Vector3& operator-=(const Vector3& right) { x -= right.x; y -= right.y; z -= right.z; return *this; }
	Vector3& operator*=(const Vector3& right) { x *= right.x; y *= right.y; z *= right.z; return *this; }
	Vector3& operator/=(const Vector3& right) { x /= right.x; y /= right.y; z /= right.z; return *this; }

	Vector3 operator+(const float& right) const { return Vector3(x + right, y + right, z + right); }
	Vector3 operator-(const float& right) const { return Vector3(x - right, y - right, z - right); }
	Vector3 operator*(const float& right) const { return Vector3(x * right, y * right, z * right); }
	Vector3 operator/(const float& right) const { return Vector3(x / right, y / right, z / right); }
	Vector3& operator=(const float& right) { x = right; y = right; z = right; return *this; }
	Vector3& operator+=(const float& right) { x += right; y += right; z += right; return *this; }
	Vector3& operator-=(const float& right) { x -= right; y -= right; z -= right; return *this; }
	Vector3& operator*=(const float& right) { x *= right; y *= right; z *= right; return *this; }
	Vector3& operator/=(const float& right) { x /= right; y /= right; z /= right; return *this; }

	// Get the cross product of two vectors
	Vector3 Cross(const Vector3 &right)
	{
		Vector3 result;
		result.x = y * right.z - z * right.y;
		result.y = z * right.x - x * right.z;
		result.z = x * right.y - y * right.x;
		return result;
	}

	// Get the length of the vector
	float Length()
	{
		return sqrtf( (x * x) + (y * y) + (z * z) );
	}

	// Get the length of the vector
	float Magnitude()
	{
		return Length();
	}

	// Get the dot product of two vectors
	float Dot(const Vector3& right)
	{
		return (x * right.x) + (y * right.y) + (z * right.z);
	}

	// Convert the vector to have a length of 1
	Vector3 Normalize()
	{
		float length = Length();
		if (length == 0.0f) return *this;

		Vector3 copy = *this;
		float norm = 1.0f / length;
		copy.x *= norm;
		copy.y *= norm;
		copy.z *= norm;

		return copy;
	}

	// Linearly interpolate between two vectors by amount t
	Vector3 Lerp(const Vector3& to, float t)
	{
		t = fmaxf(fminf(t, 1.0f), 0.0f);
		return Vector3(x + (to.x - x) * t, y + (to.y - y) * t, z + (to.z - z) * t);
	}

	// Reflects a vector off the plane defined by a normal
	Vector3 Reflect(const Vector3& normal)
	{
		float d = Dot(normal);
		return Vector3(x - 2.0f * d * normal.x, y - 2.0f * d * normal.y, z - 2.0f * d * normal.z);
	}

	// Spherically interpolate between two vectors by amount t
	Vector3 Slerp(const Vector3& to, float t)
	{
		t = fmaxf(fminf(t, 1.0f), 0.0f);
		float dot = Dot(to);
		float theta = acosf(dot);
		float sinTheta = sinf(theta);

		// Vectors are parallel
		if (sinTheta == 0.0f) {
			return Lerp(to, t);
		}	

		float w1 = sinf((1.0f - t) * theta) / sinTheta;
		float w2 = sinf(t * theta) / sinTheta;

		return Vector3(x * w1 + to.x * w2, y * w1 + to.y * w2, z * w1 + to.z * w2);
	}
	
	// Returns the distance between two vectors
	float Distance(const Vector3& other)
	{
		float dx = x - other.x;
		float dy = y - other.y;
		float dz = z - other.z;
		return sqrtf(dx * dx + dy * dy + dz * dz);
	}
};
#pragma warning(default:26495)
