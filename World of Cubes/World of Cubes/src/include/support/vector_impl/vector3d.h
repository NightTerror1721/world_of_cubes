#pragma once

#include <utility>
#include <cstdint>

#include "math.h"
#include "vector3d.h"

template<typename _Ty>
class Vector3
{
public:
	union
	{
		struct
		{
			_Ty x;
			_Ty y;
			_Ty z;
		};
		_Ty value[3];
	};

	Vector3();
	Vector3(_Ty x, _Ty y, _Ty z);
	Vector3(const Vector3& v);
	Vector3(Vector3&& v) noexcept;

	Vector3& operator= (const Vector3& v);
	Vector3& operator= (Vector3&& v) noexcept;

	operator bool() const;

	Vector3& set(_Ty x, _Ty y, _Ty z);

	double length() const;

	Vector3& normalize();
	Vector3 normalize() const;
	static Vector3 normalize(const Vector3& v);

	float distance(const Vector3& v) const;

	float dot(const Vector3& v) const;
	Vector3 cross(const Vector3& v) const;

	static float angleBetween(const Vector3& Left, const Vector3& Right);

	//static void completeOrthonormalBasis(const Vector3& Normal, Vector3& v1, Vector3& v2);

	template<typename _Ty2>
	explicit Vector3(const Vector3<_Ty2>& v);

	template<typename _Ty2>
	explicit operator Vector3<_Ty2>();

	template<typename _Ty2>
	explicit Vector3(const Vector2<_Ty2>& v, _Ty z = _Ty{});

	template<typename _Ty2>
	explicit operator Vector2<_Ty2>();

	_Ty& operator[] (size_t index);
	const _Ty& operator[] (size_t index) const;
};

template<typename _Ty>
bool operator! (const Vector3<_Ty>& v);


template<typename _Ty>
bool operator== (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
bool operator!= (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1);


template<typename _Ty>
Vector3<_Ty> operator- (const Vector3<_Ty>& v);

template<typename _Ty>
Vector3<_Ty> operator+ (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
Vector3<_Ty> operator- (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
Vector3<_Ty> operator* (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
Vector3<_Ty> operator/ (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
Vector3<_Ty> operator+ (const Vector3<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector3<_Ty> operator- (const Vector3<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector3<_Ty> operator* (const Vector3<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector3<_Ty> operator/ (const Vector3<_Ty>& v0, _Ty value);


template<typename _Ty>
Vector3<_Ty>& operator+= (Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
Vector3<_Ty>& operator+= (Vector3<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector3<_Ty>& operator-= (Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
Vector3<_Ty>& operator-= (Vector3<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector3<_Ty>& operator*= (Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
Vector3<_Ty>& operator*= (Vector3<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector3<_Ty>& operator/= (Vector3<_Ty>& v0, const Vector3<_Ty>& v1);

template<typename _Ty>
Vector3<_Ty>& operator/= (Vector3<_Ty>& v0, _Ty value);



typedef Vector3<float> vec3f;
typedef Vector3<int32_t> vec3i;
typedef Vector3<uint32_t> vec3u;

typedef vec3f vec3;




/* Implementation */

template<typename _Ty>
Vector3<_Ty>::Vector3() :
	x{},
	y{},
	z{}
{}

template<typename _Ty>
Vector3<_Ty>::Vector3(_Ty x, _Ty y, _Ty z) :
	x{ x },
	y{ y },
	z{ z }
{}

template<typename _Ty>
Vector3<_Ty>::Vector3(const Vector3& v) :
	x{ v.x },
	y{ v.y },
	z{ v.z }
{}

template<typename _Ty>
Vector3<_Ty>::Vector3(Vector3&& v) noexcept :
	x{ std::move(v.x) },
	y{ std::move(v.y) },
	z{ std::move(v.z) }
{}

template<typename _Ty>
Vector3<_Ty>& Vector3<_Ty>::operator= (const Vector3& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	return *this;
}

template<typename _Ty>
Vector3<_Ty>& Vector3<_Ty>::operator= (Vector3&& v) noexcept
{
	this->x = std::move(v.x);
	this->y = std::move(v.y);
	this->z = std::move(v.z);
	return *this;
}

template<typename _Ty>
Vector3<_Ty>::operator bool() const { return x && y && z; }

template<typename _Ty>
Vector3<_Ty>& Vector3<_Ty>::set(_Ty x, _Ty y, _Ty z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

template<typename _Ty>
double Vector3<_Ty>::length() const { return std::sqrt(x * x + y * y + z * z); }

template<typename _Ty>
Vector3<_Ty>& Vector3<_Ty>::normalize()
{
	_Ty len = static_cast<_Ty>(length());
	x /= len;
	y /= len;
	z /= len;
	return *this;
}

template<typename _Ty>
Vector3<_Ty> Vector3<_Ty>::normalize() const
{
	_Ty len = static_cast<_Ty>(length());
	return {
		x / len,
		y / len,
		z / len,
	};
}

template<typename _Ty>
Vector3<_Ty> Vector3<_Ty>::normalize(const Vector3& v) { return std::move(v.normalize()); }

template<typename _Ty>
float Vector3<_Ty>::distance(const Vector3& v) const { return (v - *this).length(); }

template<typename _Ty>
float Vector3<_Ty>::dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }

template<typename _Ty>
Vector3<_Ty> Vector3<_Ty>::cross(const Vector3& v) const { return { y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x }; }

template<typename _Ty>
float Vector3<_Ty>::angleBetween(const Vector3& left, const Vector3& right)
{
	float leftLength = static_cast<float>(left.length());
	float rightLength = static_cast<float>(right.length());
	if (leftLength > 0.0f && rightLength > 0.0f)
	{
		return std::acosf(utils::clamp(left.dot(right) / leftLength / rightLength, -1.f, 1.f));
	}
	else
	{
		return 0.0f;
	}
}

/*template<typename _Ty>
void Vector3<_Ty>::completeOrthonormalBasis(const Vector3& Normal, Vector3& v1, Vector3& v2)
{

}*/


template<typename _Ty> template<typename _Ty2>
Vector3<_Ty>::Vector3(const Vector3<_Ty2>& v) :
	x{ static_cast<_Ty>(v.x) },
	y{ static_cast<_Ty>(v.y) },
	z{ static_cast<_Ty>(v.z) }
{}

template<typename _Ty> template<typename _Ty2>
Vector3<_Ty>::operator Vector3<_Ty2>() { return Vector3<_Ty2>{ *this }; }

template<typename _Ty> template<typename _Ty2>
Vector3<_Ty>::Vector3(const Vector2<_Ty2>& v, _Ty z) :
	x{ static_cast<_Ty>(v.x) },
	y{ static_cast<_Ty>(v.y) },
	z{ z }
{}

template<typename _Ty> template<typename _Ty2>
Vector3<_Ty>::operator Vector2<_Ty2>()
{
	return { static_cast<_Ty2>(x), static_cast<_Ty2>(y) };
}

template<typename _Ty>
_Ty& Vector3<_Ty>::operator[] (size_t index)
{
	switch (index)
	{
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}
}

template<typename _Ty>
const _Ty& Vector3<_Ty>::operator[] (size_t index) const
{
	switch (index)
	{
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
	}
}


template<typename _Ty>
bool operator! (const Vector3<_Ty>& v) { return !v.x && !v.y && !v.z; }

template<typename _Ty>
bool operator== (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	return v0.x == v1.x && v0.y == v1.y && v0.z == v1.z;
}

template<typename _Ty>
bool operator!= (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	return v0.x != v1.x && v0.y != v1.y && v0.z != v1.z;
}

template<typename _Ty>
Vector3<_Ty> operator- (const Vector3<_Ty>& v) { return { -v.x, -v.y, -v.z }; }

template<typename _Ty>
Vector3<_Ty> operator+ (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	return { v0.x + v1.x, v0.y + v1.y, v0.z + v1.z };
}

template<typename _Ty>
Vector3<_Ty> operator- (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	return { v0.x + v1.x, v0.y + v1.y, v0.z - v1.z };
}

template<typename _Ty>
Vector3<_Ty> operator* (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	return { v0.x * v1.x, v0.y * v1.y, v0.z * v1.z };
}

template<typename _Ty>
Vector3<_Ty> operator/ (const Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	return { v0.x / v1.x, v0.y / v1.y, v0.z / v1.z };
}

template<typename _Ty>
Vector3<_Ty> operator+ (const Vector3<_Ty>& v0, _Ty value)
{
	return { v0.x + value, v0.y + value, v0.z + value };
}

template<typename _Ty>
Vector3<_Ty> operator- (const Vector3<_Ty>& v0, _Ty value)
{
	return { v0.x - value, v0.y - value, v0.z - value };
}

template<typename _Ty>
Vector3<_Ty> operator* (const Vector3<_Ty>& v0, _Ty value)
{
	return { v0.x * value, v0.y * value, v0.z * value };
}

template<typename _Ty>
Vector3<_Ty> operator/ (const Vector3<_Ty>& v0, _Ty value)
{
	return { v0.x / value, v0.y / value, v0.z / value };
}


template<typename _Ty>
Vector3<_Ty>& operator+= (Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	v0.x += v1.x;
	v0.y += v1.y;
	v0.z += v1.z;
	return v0;
}

template<typename _Ty>
Vector3<_Ty>& operator+= (Vector3<_Ty>& v0, _Ty value)
{
	v0.x += value;
	v0.y += value;
	v0.z += value;
	return v0;
}

template<typename _Ty>
Vector3<_Ty>& operator-= (Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	v0.x -= v1.x;
	v0.y -= v1.y;
	v0.z -= v1.z;
	return v0;
}

template<typename _Ty>
Vector3<_Ty>& operator-= (Vector3<_Ty>& v0, _Ty value)
{
	v0.x -= value;
	v0.y -= value;
	v0.z -= value;
	return v0;
}

template<typename _Ty>
Vector3<_Ty>& operator*= (Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	v0.x *= v1.x;
	v0.y *= v1.y;
	v0.z *= v1.z;
	return v0;
}

template<typename _Ty>
Vector3<_Ty>& operator*= (Vector3<_Ty>& v0, _Ty value)
{
	v0.x *= value;
	v0.y *= value;
	v0.z *= value;
	return v0;
}

template<typename _Ty>
Vector3<_Ty>& operator/= (Vector3<_Ty>& v0, const Vector3<_Ty>& v1)
{
	v0.x /= v1.x;
	v0.y /= v1.y;
	v0.z /= v1.z;
	return v0;
}

template<typename _Ty>
Vector3<_Ty>& operator/= (Vector3<_Ty>& v0, _Ty value)
{
	v0.x /= value;
	v0.y /= value;
	v0.z /= value;
	return v0;
}
