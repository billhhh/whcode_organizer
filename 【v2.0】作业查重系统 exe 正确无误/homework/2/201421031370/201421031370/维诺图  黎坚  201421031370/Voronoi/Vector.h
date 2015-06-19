#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>

struct Vector
{
	float x, y;

	Vector (float _x = 0, float _y = 0)
	{
		x = _x; y = _y;
	}

	Vector operator+(Vector& vec)
	{
		Vector vecSum;
		vecSum.x = x + vec.x;
		vecSum.y = y + vec.y;
		return vecSum;
	}

	Vector operator-(Vector& vec)
	{
		Vector vecSum;
		vecSum.x = x - vec.x;
		vecSum.y = y - vec.y;
		return vecSum;
	}

	Vector operator+=(Vector& vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	friend Vector operator*(float num, Vector& vec);
	friend Vector operator*(Vector& vec, float num);
	friend Vector operator/(Vector& vec, float num);

	void Normalize()
	{
		float amp = sqrtf(x*x + y*y);
		if (amp > fEpsilon)
		{
			x = x / amp;
			y = y / amp;
		}
	}
};

typedef Vector Vector1;

inline Vector
operator*(float num, Vector& vec)
{
	Vector vecSum;
	vecSum.x = num * vec.x;
	vecSum.y = num * vec.y;
	return vecSum;
}

inline Vector
operator*(Vector& vec, float num)
{
	Vector vecSum;
	vecSum.x = num * vec.x;
	vecSum.y = num * vec.y;
	return vecSum;
}

inline Vector
operator/(Vector& vec, float num)
{
	Vector vecOut;
	vecOut.x = vec.x / num;
	vecOut.y = vec.y / num;
	return vecOut;
}

inline Vector
Minimize (const Vector& v1, const Vector& v2)
{
   return Vector( v1.x < v2.x ? v1.x : v2.x,
                    v1.y < v2.y ? v1.y : v2.y);
}

inline Vector
Maximize (const Vector& v1, const Vector& v2)
{
   return Vector( v1.x > v2.x ? v1.x : v2.x,
                    v1.y > v2.y ? v1.y : v2.y);
}

inline float
length(const Vector& vec)
{
	return sqrtf(vec.x*vec.x + vec.y*vec.y);
}

inline float
CrossProduct2D(const Vector& v1, const Vector& v2)
{
	return (v1.x * v2.y - v1.y * v2.x);
}

struct Vector3D
{
	float x, y, z;

	Vector3D (float _x = 0, float _y = 0, float _z = 0)
	{
		x = _x; y = _y; z = _z;
	}

	Vector3D operator+(Vector3D& vec)
	{
		Vector3D vecSum;
		vecSum.x = x + vec.x;
		vecSum.y = y + vec.y;
		vecSum.z = z + vec.z;
		return vecSum;
	}

	Vector3D operator-(Vector3D& vec)
	{
		Vector3D vecSum;
		vecSum.x = x - vec.x;
		vecSum.y = y - vec.y;
		vecSum.z = z - vec.z;
		return vecSum;
	}

	friend Vector3D operator*(float num, Vector3D& vec);
	friend Vector3D operator*(Vector3D& vec, float num);

	void Normalize()
	{
		float amp = sqrtf(x*x + y*y + z*z);
		if (amp > fEpsilon)
		{
			x = x / amp;
			y = y / amp;
			z = z / amp;
		}
	}
};

inline Vector3D
operator*(float num, Vector3D& vec)
{
	Vector3D vecSum;
	vecSum.x = num * vec.x;
	vecSum.y = num * vec.y;
	vecSum.z = num * vec.z;
	return vecSum;
}

inline Vector3D
operator*(Vector3D& vec, float num)
{
	Vector3D vecSum;
	vecSum.x = num * vec.x;
	vecSum.y = num * vec.y;
	vecSum.z = num * vec.z;
	return vecSum;
}

inline Vector3D
Minimize (const Vector3D& v1, const Vector3D& v2)
{
   return Vector3D( v1.x < v2.x ? v1.x : v2.x,
                    v1.y < v2.y ? v1.y : v2.y,
                    v1.z < v2.z ? v1.z : v2.z);
}

inline Vector3D
Maximize (const Vector3D& v1, const Vector3D& v2)
{
   return Vector3D( v1.x > v2.x ? v1.x : v2.x,
                    v1.y > v2.y ? v1.y : v2.y,
                    v1.z > v2.z ? v1.z : v2.z);
}

#endif	// __VECTOR2D_H__
