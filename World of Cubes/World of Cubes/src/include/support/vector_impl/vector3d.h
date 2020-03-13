#pragma once

#include <utility>
#include <cmath>

#include "vector2d.h"

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
	Vector3& operator= (Vector3&& v);

	operator bool() const;

	Vector3& set(_Ty x, _Ty y, _Ty z);

	double length() const;

	Vector3& normalize();

	float distance(const Vector3& v);

	float dot(const Vector3& v);
	Vector3 cross(const Vector3& v);

	template<typename _Ty2>
	explicit Vector3(const Vector3<_Ty2>& v);

	template<typename _Ty2>
	explicit operator Vector3<_Ty2>();
};
