#pragma once

#include <utility>
#include <cmath>
#include <cstdint>

#include "vector2d.h"
#include "vector3d.h"

template<typename _Ty>
class Vector4
{
public:
	union
	{
		struct
		{
			_Ty x;
			_Ty y;
			_Ty z;
			_Ty w;
		};
		_Ty value[4];
	};

	Vector4();
	Vector4(_Ty x, _Ty y, _Ty z, _Ty w);
	Vector4(const Vector4& v);
	Vector4(Vector4&& v) noexcept;

	Vector4& operator= (const Vector4& v);
	Vector4& operator= (Vector4&& v) noexcept;

	operator bool() const;

	Vector4& set(_Ty x, _Ty y, _Ty z, _Ty w);

	double length() const;

	Vector4& normalize();
	Vector4 normalize() const;
	static Vector4 normalize(const Vector4& v);

	float distance(const Vector4& v);

	template<typename _Ty2>
	explicit Vector4(const Vector4<_Ty2>& v);

	template<typename _Ty2>
	explicit operator Vector4<_Ty2>();

	template<typename _Ty2>
	explicit Vector4(const Vector3<_Ty2>& v, _Ty w = _Ty{});

	template<typename _Ty2>
	explicit operator Vector3<_Ty2>();

	template<typename _Ty2>
	explicit Vector4(const Vector2<_Ty2>& v, _Ty z = _Ty{}, _Ty w = _Ty{});

	template<typename _Ty2>
	explicit operator Vector2<_Ty2>();

	_Ty& operator[] (size_t index);
	const _Ty& operator[] (size_t index) const;
};

template<typename _Ty>
bool operator! (const Vector4<_Ty>& v);


template<typename _Ty>
bool operator== (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
bool operator!= (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1);


template<typename _Ty>
Vector4<_Ty> operator+ (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
Vector4<_Ty> operator- (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
Vector4<_Ty> operator* (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
Vector4<_Ty> operator/ (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
Vector4<_Ty> operator+ (const Vector4<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector4<_Ty> operator- (const Vector4<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector4<_Ty> operator* (const Vector4<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector4<_Ty> operator/ (const Vector4<_Ty>& v0, _Ty value);


template<typename _Ty>
Vector4<_Ty>& operator+= (Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
Vector4<_Ty>& operator+= (Vector4<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector4<_Ty>& operator-= (Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
Vector4<_Ty>& operator-= (Vector4<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector4<_Ty>& operator*= (Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
Vector4<_Ty>& operator*= (Vector4<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector4<_Ty>& operator/= (Vector4<_Ty>& v0, const Vector4<_Ty>& v1);

template<typename _Ty>
Vector4<_Ty>& operator/= (Vector4<_Ty>& v0, _Ty value);



typedef Vector4<float> vec4f;
typedef Vector4<int32_t> vec4i;
typedef Vector4<uint32_t> vec4u;

typedef vec4f vec4;





/* Implementation */

template<typename _Ty>
Vector4<_Ty>::Vector4() :
	x{},
	y{},
	z{},
	w{}
{}

template<typename _Ty>
Vector4<_Ty>::Vector4(_Ty x, _Ty y, _Ty z, _Ty w) :
	x{ x },
	y{ y },
	z{ z },
	w{ w }
{}

template<typename _Ty>
Vector4<_Ty>::Vector4(const Vector4& v) :
	x{ v.x },
	y{ v.y },
	z{ v.z },
	w{ v.w }
{}

template<typename _Ty>
Vector4<_Ty>::Vector4(Vector4&& v) noexcept :
	x{ std::move(v.x) },
	y{ std::move(v.y) },
	z{ std::move(v.z) },
	w{ std::move(v.w) }
{}

template<typename _Ty>
Vector4<_Ty>& Vector4<_Ty>::operator= (const Vector4& v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
	return *this;
}

template<typename _Ty>
Vector4<_Ty>& Vector4<_Ty>::operator= (Vector4&& v) noexcept
{
	this->x = std::move(v.x);
	this->y = std::move(v.y);
	this->z = std::move(v.z);
	this->w = std::move(v.w);
	return *this;
}

template<typename _Ty>
Vector4<_Ty>::operator bool() const { return x && y && z && w; }

template<typename _Ty>
Vector4<_Ty>& Vector4<_Ty>::set(_Ty x, _Ty y, _Ty z, _Ty w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	return *this;
}

template<typename _Ty>
double Vector4<_Ty>::length() const { return std::sqrt(x * x + y * y + z * z + w * w); }

template<typename _Ty>
Vector4<_Ty>& Vector4<_Ty>::normalize()
{
	double len = length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
	return *this;
}

template<typename _Ty>
Vector4<_Ty> Vector4<_Ty>::normalize() const
{
	double len = length();
	return {
		x / len,
		y / len,
		z / len,
	};
}

template<typename _Ty>
Vector4<_Ty> Vector4<_Ty>::normalize(const Vector4& v) { return std::move(v.normalize()); }

template<typename _Ty>
float Vector4<_Ty>::distance(const Vector4& v) { return (v - *this).length(); }

template<typename _Ty> template<typename _Ty2>
Vector4<_Ty>::Vector4(const Vector4<_Ty2>& v) :
	x{ static_cast<_Ty>(v.x) },
	y{ static_cast<_Ty>(v.y) },
	z{ static_cast<_Ty>(v.z) },
	w{ static_cast<_Ty>(v.w) }
{}

template<typename _Ty> template<typename _Ty2>
Vector4<_Ty>::operator Vector4<_Ty2>() { return Vector4<_Ty2>{ *this }; }

template<typename _Ty> template<typename _Ty2>
Vector4<_Ty>::Vector4(const Vector3<_Ty2>& v, _Ty w) :
	x{ static_cast<_Ty>(v.x) },
	y{ static_cast<_Ty>(v.y) },
	z{ static_cast<_Ty>(v.z) },
	w{ w }
{}

template<typename _Ty> template<typename _Ty2>
Vector4<_Ty>::operator Vector3<_Ty2>()
{
	return { static_cast<_Ty2>(x), static_cast<_Ty2>(y), static_cast<_Ty2>(z) };
}

template<typename _Ty> template<typename _Ty2>
Vector4<_Ty>::Vector4(const Vector2<_Ty2>& v, _Ty z, _Ty w) :
	x{ static_cast<_Ty>(v.x) },
	y{ static_cast<_Ty>(v.y) },
	z{ z },
	w{ w }
{}

template<typename _Ty> template<typename _Ty2>
Vector4<_Ty>::operator Vector2<_Ty2>()
{
	return { static_cast<_Ty2>(x), static_cast<_Ty2>(y) };
}

template<typename _Ty>
_Ty& Vector4<_Ty>::operator[] (size_t index)
{
	switch (index)
	{
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
}

template<typename _Ty>
const _Ty& Vector4<_Ty>::operator[] (size_t index) const
{
	switch (index)
	{
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
}


template<typename _Ty>
bool operator! (const Vector4<_Ty>& v) { return !v.x && !v.y && !v.z && !v.w; }

template<typename _Ty>
bool operator== (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	return v0.x == v1.x && v0.y == v1.y && v0.z == v1.z && v0.w == v1.w;
}

template<typename _Ty>
bool operator!= (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	return v0.x != v1.x && v0.y != v1.y && v0.z != v1.z && v0.w != v1.w;
}

template<typename _Ty>
Vector4<_Ty> operator+ (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	return { v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w };
}

template<typename _Ty>
Vector4<_Ty> operator- (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	return { v0.x + v1.x, v0.y + v1.y, v0.z - v1.z, v0.w - v1.w };
}

template<typename _Ty>
Vector4<_Ty> operator* (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	return { v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w };
}

template<typename _Ty>
Vector4<_Ty> operator/ (const Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	return { v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w };
}

template<typename _Ty>
Vector4<_Ty> operator+ (const Vector4<_Ty>& v0, _Ty value)
{
	return { v0.x + value, v0.y + value, v0.z + value, v0.w + value };
}

template<typename _Ty>
Vector4<_Ty> operator- (const Vector4<_Ty>& v0, _Ty value)
{
	return { v0.x - value, v0.y - value, v0.z - value, v0.w - value };
}

template<typename _Ty>
Vector4<_Ty> operator* (const Vector4<_Ty>& v0, _Ty value)
{
	return { v0.x * value, v0.y * value, v0.z * value, v0.w * value };
}

template<typename _Ty>
Vector4<_Ty> operator/ (const Vector4<_Ty>& v0, _Ty value)
{
	return { v0.x / value, v0.y / value, v0.z / value, v0.w / value };
}


template<typename _Ty>
Vector4<_Ty>& operator+= (Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	v0.x += v1.x;
	v0.y += v1.y;
	v0.z += v1.z;
	v0.w += v1.w;
	return v0;
}

template<typename _Ty>
Vector4<_Ty>& operator+= (Vector4<_Ty>& v0, _Ty value)
{
	v0.x += value;
	v0.y += value;
	v0.z += value;
	v0.w += value;
	return v0;
}

template<typename _Ty>
Vector4<_Ty>& operator-= (Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	v0.x -= v1.x;
	v0.y -= v1.y;
	v0.z -= v1.z;
	v0.w -= v1.w;
	return v0;
}

template<typename _Ty>
Vector4<_Ty>& operator-= (Vector4<_Ty>& v0, _Ty value)
{
	v0.x -= value;
	v0.y -= value;
	v0.z -= value;
	v0.w -= value;
	return v0;
}

template<typename _Ty>
Vector4<_Ty>& operator*= (Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	v0.x *= v1.x;
	v0.y *= v1.y;
	v0.z *= v1.z;
	v0.w *= v1.w;
	return v0;
}

template<typename _Ty>
Vector4<_Ty>& operator*= (Vector4<_Ty>& v0, _Ty value)
{
	v0.x *= value;
	v0.y *= value;
	v0.z *= value;
	v0.w *= value;
	return v0;
}

template<typename _Ty>
Vector4<_Ty>& operator/= (Vector4<_Ty>& v0, const Vector4<_Ty>& v1)
{
	v0.x /= v1.x;
	v0.y /= v1.y;
	v0.z /= v1.z;
	v0.w /= v1.w;
	return v0;
}

template<typename _Ty>
Vector4<_Ty>& operator/= (Vector4<_Ty>& v0, _Ty value)
{
	v0.x /= value;
	v0.y /= value;
	v0.z /= value;
	v0.w /= value;
	return v0;
}
