#pragma once

#include "vectors.h"

class Matrix4x4
{
public:
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		struct
		{
			vec4f row0;
			vec4f row1;
			vec4f row2;
			vec4f row3;
		};
		float mat[4][4];
		vec4f rows[4];
		float values[16];
	};

	enum class RowId : size_t { r0, r1, r2, r3 };
	enum class ColumnId : size_t { c0, c1, c2, c3 };

	static constexpr RowId Row0{ RowId::r0 };
	static constexpr RowId Row1{ RowId::r1 };
	static constexpr RowId Row2{ RowId::r2 };
	static constexpr RowId Row3{ RowId::r3 };

	static constexpr ColumnId Column0{ ColumnId::c0 };
	static constexpr ColumnId Column1{ ColumnId::c1 };
	static constexpr ColumnId Column2{ ColumnId::c2 };
	static constexpr ColumnId Column3{ ColumnId::c3 };

	Matrix4x4();
	Matrix4x4(const vec4f& row0, const vec4f& row1, const vec4f& row2, const vec4f& row3);
	Matrix4x4(const vec3f& v0, const vec3f& v1, const vec3f& v2);
	Matrix4x4(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44
	);
	Matrix4x4(const Matrix4x4& m);
	Matrix4x4(Matrix4x4&& m) noexcept;

	Matrix4x4& operator= (const Matrix4x4& m);
	Matrix4x4& operator= (Matrix4x4&& m) noexcept;

	vec4f& operator[] (size_t index);
	const vec4f& operator[] (size_t index) const;

	inline vec4f& operator[] (RowId row) { return operator[](static_cast<size_t>(row)); }
	inline const vec4f& operator[] (RowId row) const { return operator[](static_cast<size_t>(row)); }

	Matrix4x4& setIdentity();

	//float determinant() const;
	Matrix4x4 transpose() const;
	Matrix4x4 invert() const;

	vec3f transformPoint(const vec3f& point) const;
	vec3f transformNormal(const vec3f& normal) const;

	inline void setRow(size_t index, const vec4f& v) { operator[](index) = v; }
	inline void setRow(RowId row, const vec4f& v) { operator[](row) = v; }

	inline const vec4f& getRow(size_t index) { return operator[](index); }
	inline const vec4f& getRow(RowId row) { return operator[](row); }

	void setColumn(size_t index, const vec4f& v);
	inline void setColumn(ColumnId column, const vec4f& v) { setColumn(static_cast<size_t>(column), v); }

	vec4f getColumn(size_t index);
	inline vec4f getColumn(ColumnId column) { return std::move(getColumn(static_cast<size_t>(column))); }

	inline vec3f rightVector() { return { values[0], values[1], values[2] }; }
	inline vec3f topVector() { return { values[4], values[5], values[6] }; }
	inline vec3f frontVector() { return { values[8], values[9], values[10] }; }


	Matrix4x4 scale(const vec3f& scaleFactors);

	Matrix4x4 translate(const vec3f& pos);

	Matrix4x4 rotate(const vec3f& axis, float angle, const vec3f& center);
	Matrix4x4 rotate(const vec3f& axis, float angle);
	Matrix4x4 rotate(float yaw, float pitch, float roll);
	Matrix4x4 rotate(const vec3f& basis1, const vec3f& basis2, const vec3f& basis3);

	Matrix4x4 rotateX(float theta);
	Matrix4x4 rotateY(float theta);
	Matrix4x4 rotateZ(float theta);


	Matrix4x4 localScale(const vec3f& scaleFactors);

	Matrix4x4 localTranslate(const vec3f& pos);

	Matrix4x4 localRotate(const vec3f& axis, float angle, const vec3f& center);
	Matrix4x4 localRotate(const vec3f& axis, float angle);
	Matrix4x4 localRotate(float yaw, float pitch, float roll);
	Matrix4x4 localRotate(const vec3f& basis1, const vec3f& basis2, const vec3f& basis3);

	Matrix4x4 localRotateX(float theta);
	Matrix4x4 localRotateY(float theta);
	Matrix4x4 localRotateZ(float theta);



	static inline Matrix4x4 identity() { return {}; }

	static Matrix4x4 scaling(const vec3f& scaleFactors);
	static inline Matrix4x4 scaling(float scaleFactor) { return scaling({ scaleFactor, scaleFactor, scaleFactor }); }

	static Matrix4x4 translation(const vec3f& pos);

	static Matrix4x4 rotation(const vec3f& axis, float angle, const vec3f& center);
	static Matrix4x4 rotation(const vec3f& axis, float angle);
	static Matrix4x4 rotation(float yaw, float pitch, float roll);
	static Matrix4x4 rotation(const vec3f& basis1, const vec3f& basis2, const vec3f& basis3);

	static Matrix4x4 rotationX(float theta);
	static Matrix4x4 rotationY(float theta);
	static Matrix4x4 rotationZ(float theta);

	static Matrix4x4 camera(const vec3f& eye, const vec3f& look, const vec3f& up, const vec3f& right);
	static Matrix4x4 lookAt(const vec3f& eye, const vec3f& at, const vec3f& up);
	static Matrix4x4 orthogonal(float width, float height, float zNear, float zFar);
	static Matrix4x4 perspective(float width, float height, float zNear, float zFar);
	static Matrix4x4 perspectiveFov(float fov, float aspect, float zNear, float zFar);
	static Matrix4x4 perspectiveMultiFov(float fovX, float fovY, float zNear, float zFar);
	//static Matrix4x4 face(const vec3f& v0, const vec3f& v1);
	static Matrix4x4 viewport(float width, float height);
	static Matrix4x4 changeOfBasis(
		const vec3f& source0,
		const vec3f& source1,
		const vec3f& source2,
		const vec3f& sourceOrigin,
		const vec3f& target0,
		const vec3f& target1,
		const vec3f& target2,
		const vec3f& targetOrigin
	);
	static float compareMatrices(const Matrix4x4& left, const Matrix4x4& right);
};

Matrix4x4 operator+ (const Matrix4x4& m0, const Matrix4x4& m1);
Matrix4x4 operator- (const Matrix4x4& m0, const Matrix4x4& m1);

Matrix4x4 operator* (const Matrix4x4& m0, const Matrix4x4& m1);
Matrix4x4 operator* (const Matrix4x4& m, float value);
Matrix4x4 operator* (float value, const Matrix4x4& m);

Matrix4x4& operator+= (Matrix4x4& m0, const Matrix4x4& m1);
Matrix4x4& operator-= (Matrix4x4& m0, const Matrix4x4& m1);

Matrix4x4& operator*= (Matrix4x4& m0, const Matrix4x4& m1);
Matrix4x4& operator*= (Matrix4x4& m, float value);




typedef Matrix4x4 mat4;
typedef Matrix4x4 mat44;
