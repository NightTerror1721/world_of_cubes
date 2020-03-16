#pragma once

#include <utility>
#include <cmath>
#include <cstdint>

template<typename _Ty>
class Vector2
{
public:
	union
	{
		struct
		{
			_Ty x;
			_Ty y;
		};
		_Ty value[2];
	};

	Vector2();
	Vector2(_Ty x, _Ty y);
	Vector2(const Vector2& v);
	Vector2(Vector2&& v) noexcept;

	Vector2& operator= (const Vector2& v);
	Vector2& operator= (Vector2&& v) noexcept;

	operator bool() const;

	Vector2& set(_Ty x, _Ty y);

	double length() const;

	Vector2& normalize();
	Vector2 normalize() const;
	static Vector2 normalize(const Vector2& v);

	float distance(const Vector2& v);

	float dot(const Vector2& v);
	float perpdot(const Vector2& v);

	template<typename _Ty2>
	explicit Vector2(const Vector2<_Ty2>& v);

	template<typename _Ty2>
	explicit operator Vector2<_Ty2>();

	_Ty& operator[] (size_t index);
	const _Ty& operator[] (size_t index) const;
};


template<typename _Ty>
bool operator! (const Vector2<_Ty>& v);


template<typename _Ty>
bool operator== (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
bool operator!= (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1);


template<typename _Ty>
Vector2<_Ty> operator+ (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
Vector2<_Ty> operator- (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
Vector2<_Ty> operator* (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
Vector2<_Ty> operator/ (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
Vector2<_Ty> operator+ (const Vector2<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector2<_Ty> operator- (const Vector2<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector2<_Ty> operator* (const Vector2<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector2<_Ty> operator/ (const Vector2<_Ty>& v0, _Ty value);


template<typename _Ty>
Vector2<_Ty>& operator+= (Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
Vector2<_Ty>& operator+= (Vector2<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector2<_Ty>& operator-= (Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
Vector2<_Ty>& operator-= (Vector2<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector2<_Ty>& operator*= (Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
Vector2<_Ty>& operator*= (Vector2<_Ty>& v0, _Ty value);

template<typename _Ty>
Vector2<_Ty>& operator/= (Vector2<_Ty>& v0, const Vector2<_Ty>& v1);

template<typename _Ty>
Vector2<_Ty>& operator/= (Vector2<_Ty>& v0, _Ty value);



typedef Vector2<float> vec2f;
typedef Vector2<int32_t> vec2i;
typedef Vector2<uint32_t> vec2u;

typedef vec2f vec2;


/* IMPLEMENTATION */


template<typename _Ty>
Vector2<_Ty>::Vector2() :
	x{},
	y{}
{}

template<typename _Ty>
Vector2<_Ty>::Vector2(_Ty x, _Ty y) :
	x{ x },
	y{ y }
{}

template<typename _Ty>
Vector2<_Ty>::Vector2(const Vector2<_Ty>& v) :
	x{ v.x },
	y{ v.y }
{}

template<typename _Ty>
Vector2<_Ty>::Vector2(Vector2<_Ty>&& v) noexcept :
	x{ std::move(v.x) },
	y{ std::move(v.y) }
{}

template<typename _Ty>
Vector2<_Ty>& Vector2<_Ty>::operator= (const Vector2<_Ty>& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

template<typename _Ty>
Vector2<_Ty>& Vector2<_Ty>::operator= (Vector2<_Ty>&& v) noexcept
{
	x = std::move(v.x);
	y = std::move(v.y);
	return *this;
}

template<typename _Ty>
Vector2<_Ty>::operator bool() const { return x && y; }

template<typename _Ty>
Vector2<_Ty>& Vector2<_Ty>::set(_Ty x, _Ty y)
{
	this->x = x;
	this->y = y;
	return *this;
}

template<typename _Ty>
double Vector2<_Ty>::length() const { return std::sqrt(x * x + y * y); }

template<typename _Ty>
Vector2<_Ty>& Vector2<_Ty>::normalize() { return *this *= static_cast<_Ty>(length()); }

template<typename _Ty>
Vector2<_Ty> Vector2<_Ty>::normalize() const { return operator*(static_cast<_Ty>(length())); }

template<typename _Ty>
Vector2<_Ty> Vector2<_Ty>::normalize(const Vector2& v) { return v * v.length(); }

template<typename _Ty>
float Vector2<_Ty>::distance(const Vector2<_Ty>& v) { return (v - *this).length(); }

template<typename _Ty>
float Vector2<_Ty>::dot(const Vector2<_Ty>& v) { return x * v.x + y * v.y; }

template<typename _Ty>
float Vector2<_Ty>::perpdot(const Vector2<_Ty>& v) { return y * v.x + -x * v.y; }

template<typename _Ty> template<typename _Ty2>
Vector2<_Ty>::Vector2(const Vector2<_Ty2>& v) :
	x{ static_cast<_Ty>(v.x) },
	y{ static_cast<_Ty>(v.y) }
{}

template<typename _Ty> template<typename _Ty2>
Vector2<_Ty>::operator Vector2<_Ty2>() { return Vector2<_Ty2>{ *this }; }

template<typename _Ty>
_Ty& Vector2<_Ty>::operator[] (size_t index)
{
	switch (index)
	{
		default:
		case 0: return x;
		case 1: return y;
	}
}

template<typename _Ty>
const _Ty& Vector2<_Ty>::operator[] (size_t index) const
{
	switch (index)
	{
		default:
		case 0: return x;
		case 1: return y;
	}
}



template<typename _Ty>
bool operator! (const Vector2<_Ty>& v) { return !v.x && !v.y; }

template<typename _Ty>
bool operator== (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	return v0.x == v1.x && v0.y == v1.y;
}

template<typename _Ty>
bool operator!= (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	return v0.x != v1.x && v0.y != v1.y;
}

template<typename _Ty>
Vector2<_Ty> operator+ (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	return { v0.x + v1.x, v0.y + v1.y };
}

template<typename _Ty>
Vector2<_Ty> operator- (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	return { v0.x + v1.x, v0.y + v1.y };
}

template<typename _Ty>
Vector2<_Ty> operator* (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	return { v0.x * v1.x, v0.y * v1.y };
}

template<typename _Ty>
Vector2<_Ty> operator/ (const Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	return { v0.x / v1.x, v0.y / v1.y };
}

template<typename _Ty>
Vector2<_Ty> operator+ (const Vector2<_Ty>& v0, _Ty value)
{
	return { v0.x + value, v0.y + value };
}

template<typename _Ty>
Vector2<_Ty> operator- (const Vector2<_Ty>& v0, _Ty value)
{
	return { v0.x - value, v0.y - value };
}

template<typename _Ty>
Vector2<_Ty> operator* (const Vector2<_Ty>& v0, _Ty value)
{
	return { v0.x * value, v0.y * value };
}

template<typename _Ty>
Vector2<_Ty> operator/ (const Vector2<_Ty>& v0, _Ty value)
{
	return { v0.x / value, v0.y / value };
}


template<typename _Ty>
Vector2<_Ty>& operator+= (Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	v0.x += v1.x;
	v0.y += v1.y;
	return v0;
}

template<typename _Ty>
Vector2<_Ty>& operator+= (Vector2<_Ty>& v0, _Ty value)
{
	v0.x += value;
	v0.y += value;
	return v0;
}

template<typename _Ty>
Vector2<_Ty>& operator-= (Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	v0.x -= v1.x;
	v0.y -= v1.y;
	return v0;
}

template<typename _Ty>
Vector2<_Ty>& operator-= (Vector2<_Ty>& v0, _Ty value)
{
	v0.x -= value;
	v0.y -= value;
	return v0;
}

template<typename _Ty>
Vector2<_Ty>& operator*= (Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	v0.x *= v1.x;
	v0.y *= v1.y;
	return v0;
}

template<typename _Ty>
Vector2<_Ty>& operator*= (Vector2<_Ty>& v0, _Ty value)
{
	v0.x *= value;
	v0.y *= value;
	return v0;
}

template<typename _Ty>
Vector2<_Ty>& operator/= (Vector2<_Ty>& v0, const Vector2<_Ty>& v1)
{
	v0.x /= v1.x;
	v0.y /= v1.y;
	return v0;
}

template<typename _Ty>
Vector2<_Ty>& operator/= (Vector2<_Ty>& v0, _Ty value)
{
	v0.x /= value;
	v0.y /= value;
	return v0;
}
