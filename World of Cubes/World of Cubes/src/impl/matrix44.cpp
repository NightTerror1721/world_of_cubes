#include "support/matrix44.h"

#include <cmath>

Matrix4x4::Matrix4x4() :
	_11{ 1 }, _12{ 0 }, _13{ 0 }, _14{ 0 },
	_21{ 0 }, _22{ 1 }, _23{ 0 }, _24{ 0 },
	_31{ 0 }, _32{ 0 }, _33{ 1 }, _34{ 0 },
	_41{ 0 }, _42{ 0 }, _43{ 0 }, _44{ 1 }
{}
Matrix4x4::Matrix4x4(const vec4f& row0, const vec4f& row1, const vec4f& row2, const vec4f& row3) :
	_11{ row0.x }, _12{ row0.y }, _13{ row0.z }, _14{ row0.w },
	_21{ row1.x }, _22{ row1.y }, _23{ row1.z }, _24{ row1.w },
	_31{ row2.x }, _32{ row2.y }, _33{ row2.z }, _34{ row2.w },
	_41{ row3.x }, _42{ row3.y }, _43{ row3.z }, _44{ row3.w }
{}
Matrix4x4::Matrix4x4(const vec3f& v0, const vec3f& v1, const vec3f& v2) :
	_11{ v0.x }, _12{ v0.y }, _13{ v0.z }, _14{ 0 },
	_21{ v1.x }, _22{ v1.y }, _23{ v1.z }, _24{ 0 },
	_31{ v2.x }, _32{ v2.y }, _33{ v2.z }, _34{ 0 },
	_41{ 0 },    _42{ 0 },    _43{ 0 },    _44{ 1 }
{}
Matrix4x4::Matrix4x4(
	float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44
) :
	_11{ _11 }, _12{ _12 }, _13{ _13 }, _14{ _14 },
	_21{ _21 }, _22{ _22 }, _23{ _23 }, _24{ _24 },
	_31{ _31 }, _32{ _32 }, _33{ _33 }, _34{ _34 },
	_41{ _41 }, _42{ _42 }, _43{ _43 }, _44{ _44 }
{}
Matrix4x4::Matrix4x4(const Matrix4x4& m) :
	_11{ m._11 }, _12{ m._12 }, _13{ m._13 }, _14{ m._14 },
	_21{ m._21 }, _22{ m._22 }, _23{ m._23 }, _24{ m._24 },
	_31{ m._31 }, _32{ m._32 }, _33{ m._33 }, _34{ m._34 },
	_41{ m._41 }, _42{ m._42 }, _43{ m._43 }, _44{ m._44 }
{}
Matrix4x4::Matrix4x4(Matrix4x4&& m) noexcept :
	_11{ std::move(m._11) }, _12{ std::move(m._12) }, _13{ std::move(m._13) }, _14{ std::move(m._14) },
	_21{ std::move(m._21) }, _22{ std::move(m._22) }, _23{ std::move(m._23) }, _24{ std::move(m._24) },
	_31{ std::move(m._31) }, _32{ std::move(m._32) }, _33{ std::move(m._33) }, _34{ std::move(m._34) },
	_41{ std::move(m._41) }, _42{ std::move(m._42) }, _43{ std::move(m._43) }, _44{ std::move(m._44) }
{}

Matrix4x4& Matrix4x4::operator= (const Matrix4x4& m)
{
	_11 = m._11; _12 = m._12; _13 = m._13; _14 = m._14;
	_21 = m._21; _22 = m._22; _23 = m._23; _24 = m._24;
	_31 = m._31; _32 = m._32; _33 = m._33; _34 = m._34;
	_41 = m._41; _42 = m._42; _43 = m._43; _44 = m._44;
	return *this;
}
Matrix4x4& Matrix4x4::operator= (Matrix4x4&& m) noexcept
{
	_11 = std::move(m._11); _12 = std::move(m._12); _13 = std::move(m._13); _14 = std::move(m._14);
	_21 = std::move(m._21); _22 = std::move(m._22); _23 = std::move(m._23); _24 = std::move(m._24);
	_31 = std::move(m._31); _32 = std::move(m._32); _33 = std::move(m._33); _34 = std::move(m._34);
	_41 = std::move(m._41); _42 = std::move(m._42); _43 = std::move(m._43); _44 = std::move(m._44);
	return *this;
}

vec4f& Matrix4x4::operator[] (size_t index)
{
    switch (index)
    {
        default:
        case 0: return row0;
        case 1: return row1;
        case 2: return row2;
        case 3: return row3;
    }
}

const vec4f& Matrix4x4::operator[] (size_t index) const
{
    switch (index)
    {
        default:
        case 0: return row0;
        case 1: return row1;
        case 2: return row2;
        case 3: return row3;
    }
}

Matrix4x4& Matrix4x4::setIdentity()
{
	_11 = 1; _12 = 0; _13 = 0; _14 = 0;
	_21 = 0; _22 = 1; _23 = 0; _24 = 0;
	_31 = 0; _32 = 0; _33 = 1; _34 = 0;
	_41 = 0; _42 = 0; _43 = 0; _44 = 1;
	return *this;
}

/*float Matrix4x4::determinant() const
{

}*/

Matrix4x4 Matrix4x4::transpose() const
{
    return {
        _11, _21, _31, _41,
        _12, _22, _32, _42,
        _13, _23, _33, _43,
        _14, _24, _34, _44
    };
}

Matrix4x4 Matrix4x4::invert() const
{
    float result[4][4];
    float tmp[12]; /* temp array for pairs */
    float src[16]; /* array of transpose source matrix */
    float det; /* determinant */

    /* transpose matrix */
    for (unsigned int i = 0; i < 4; i++)
    {
        src[i + 0] = mat[i][0];
        src[i + 4] = mat[i][1];
        src[i + 8] = mat[i][2];
        src[i + 12] = mat[i][3];
    }

    /* calculate pairs for first 8 elements (cofactors) */
    tmp[0] = src[10] * src[15];
    tmp[1] = src[11] * src[14];
    tmp[2] = src[9] * src[15];
    tmp[3] = src[11] * src[13];
    tmp[4] = src[9] * src[14];
    tmp[5] = src[10] * src[13];
    tmp[6] = src[8] * src[15];
    tmp[7] = src[11] * src[12];
    tmp[8] = src[8] * src[14];
    tmp[9] = src[10] * src[12];
    tmp[10] = src[8] * src[13];
    tmp[11] = src[9] * src[12];

    /* calculate first 8 elements (cofactors) */
    result[0][0] = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4] * src[7];
    result[0][0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5] * src[7];
    result[0][1] = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9] * src[7];
    result[0][1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8] * src[7];
    result[0][2] = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
    result[0][2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
    result[0][3] = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
    result[0][3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
    result[1][0] = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5] * src[3];
    result[1][0] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4] * src[3];
    result[1][1] = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8] * src[3];
    result[1][1] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9] * src[3];
    result[1][2] = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
    result[1][2] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
    result[1][3] = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
    result[1][3] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

    /* calculate pairs for second 8 elements (cofactors) */
    tmp[0] = src[2] * src[7];
    tmp[1] = src[3] * src[6];
    tmp[2] = src[1] * src[7];
    tmp[3] = src[3] * src[5];
    tmp[4] = src[1] * src[6];
    tmp[5] = src[2] * src[5];

    tmp[6] = src[0] * src[7];
    tmp[7] = src[3] * src[4];
    tmp[8] = src[0] * src[6];
    tmp[9] = src[2] * src[4];
    tmp[10] = src[0] * src[5];
    tmp[11] = src[1] * src[4];

    /* calculate second 8 elements (cofactors) */
    result[2][0] = tmp[0] * src[13] + tmp[3] * src[14] + tmp[4] * src[15];
    result[2][0] -= tmp[1] * src[13] + tmp[2] * src[14] + tmp[5] * src[15];
    result[2][1] = tmp[1] * src[12] + tmp[6] * src[14] + tmp[9] * src[15];
    result[2][1] -= tmp[0] * src[12] + tmp[7] * src[14] + tmp[8] * src[15];
    result[2][2] = tmp[2] * src[12] + tmp[7] * src[13] + tmp[10] * src[15];
    result[2][2] -= tmp[3] * src[12] + tmp[6] * src[13] + tmp[11] * src[15];
    result[2][3] = tmp[5] * src[12] + tmp[8] * src[13] + tmp[11] * src[14];
    result[2][3] -= tmp[4] * src[12] + tmp[9] * src[13] + tmp[10] * src[14];
    result[3][0] = tmp[2] * src[10] + tmp[5] * src[11] + tmp[1] * src[9];
    result[3][0] -= tmp[4] * src[11] + tmp[0] * src[9] + tmp[3] * src[10];
    result[3][1] = tmp[8] * src[11] + tmp[0] * src[8] + tmp[7] * src[10];
    result[3][1] -= tmp[6] * src[10] + tmp[9] * src[11] + tmp[1] * src[8];
    result[3][2] = tmp[6] * src[9] + tmp[11] * src[11] + tmp[3] * src[8];
    result[3][2] -= tmp[10] * src[11] + tmp[2] * src[8] + tmp[7] * src[9];
    result[3][3] = tmp[10] * src[10] + tmp[4] * src[8] + tmp[9] * src[9];
    result[3][3] -= tmp[8] * src[9] + tmp[11] * src[10] + tmp[5] * src[8];
    /* calculate determinant */
    det = src[0] * result[0][0] + src[1] * result[0][1] + src[2] * result[0][2] + src[3] * result[0][3];
    /* calculate matrix inverse */
    det = 1.0f / det;

    Matrix4x4 floatResult;
    for (unsigned int i = 0; i < 4; i++)
    {
        for (unsigned int j = 0; j < 4; j++)
        {
            floatResult.mat[i][j] = float(result[i][j] * det);
        }
    }
    return std::move(floatResult);
}

vec3f Matrix4x4::transformPoint(const vec3f& point) const
{
    float w = point.x * mat[0][3] + point.y * mat[1][3] + point.z * mat[2][3] + mat[3][3];
    if (w)
    {
        const float invW = 1.0f / w;
        return {
            (point.x * mat[0][0] + point.y * mat[1][0] + point.z * mat[2][0] + mat[3][0]) * invW,
            (point.x * mat[0][1] + point.y * mat[1][1] + point.z * mat[2][1] + mat[3][1]) * invW,
            (point.x * mat[0][2] + point.y * mat[1][2] + point.z * mat[2][2] + mat[3][2]) * invW
        };
    }

    return {};
}

vec3f Matrix4x4::transformNormal(const vec3f& normal) const
{
    return {
        normal.x * mat[0][0] + normal.y * mat[1][0] + normal.z * mat[2][0],
        normal.x * mat[0][1] + normal.y * mat[1][1] + normal.z * mat[2][1],
        normal.x * mat[0][2] + normal.y * mat[1][2] + normal.z * mat[2][2]
    };
}

void Matrix4x4::setColumn(size_t index, const vec4f& v)
{
    switch (index)
    {
        default:
        case 0: _11 = v.x; _21 = v.y; _31 = v.z; _41 = v.w;
        case 1: _12 = v.x; _22 = v.y; _32 = v.z; _42 = v.w;
        case 2: _13 = v.x; _23 = v.y; _33 = v.z; _43 = v.w;
        case 3: _14 = v.x; _24 = v.y; _34 = v.z; _44 = v.w;
    }
}

vec4f Matrix4x4::getColumn(size_t index)
{
    switch (index)
    {
        default:
        case 0: return { _11, _21, _31, _41 };
        case 1: return { _12, _22, _32, _42 };
        case 2: return { _13, _23, _33, _43 };
        case 3: return { _14, _24, _34, _44 };
    }
}

Matrix4x4 Matrix4x4::scaling(const vec3f& scaleFactors);

Matrix4x4 Matrix4x4::translation(const vec3f& pos);

Matrix4x4 Matrix4x4::rotation(const vec3f& axis, float angle, const vec3f& center);
Matrix4x4 Matrix4x4::rotation(const vec3f& axis, float angle)
{
    float c = std::cosf(angle);
    float s = std::sinf(angle);
    float t = 1.0f - c;

    vec3f normalizedAxis = axis.normalize();
    float x = normalizedAxis.x;
    float y = normalizedAxis.y;
    float z = normalizedAxis.z;

    Matrix4x4 result;
    result.mat[0][0] = 1 + t * (x * x - 1);
    result.mat[0][1] = z * s + t * x * y;
    result.mat[0][2] = -y * s + t * x * z;
    result.mat[0][3] = 0.0f;

    result.mat[1][0] = -z * s + t * x * y;
    result.mat[1][1] = 1 + t * (y * y - 1);
    result.mat[1][2] = x * s + t * y * z;
    result.mat[1][3] = 0.0f;

    result.mat[2][0] = y * s + t * x * z;
    result.mat[2][1] = -x * s + t * y * z;
    result.mat[2][2] = 1 + t * (z * z - 1);
    result.mat[2][3] = 0.0f;

    result.mat[3][0] = 0.0f;
    result.mat[3][1] = 0.0f;
    result.mat[3][2] = 0.0f;
    result.mat[3][3] = 1.0f;
    return result;
}
Matrix4x4 Matrix4x4::rotation(float yaw, float pitch, float roll);
Matrix4x4 Matrix4x4::rotation(const vec3f& _basis1, const vec3f& _basis2, const vec3f& _basis3)
{
    vec3f basis1 = _basis1.normalize();
    vec3f basis2 = _basis2.normalize();
    vec3f basis3 = _basis3.normalize();

    Matrix4x4 result;
    result.mat[0][0] = basis1.x;
    result.mat[1][0] = basis2.y;
    result.mat[2][0] = basis3.z;
    result.mat[3][0] = 0.0f;

    result.mat[0][1] = basis1.x;
    result.mat[1][1] = basis2.y;
    result.mat[2][1] = basis3.z;
    result.mat[3][1] = 0.0f;

    result.mat[0][2] = basis1.x;
    result.mat[1][2] = basis2.y;
    result.mat[2][2] = basis3.z;
    result.mat[3][2] = 0.0f;

    result.mat[0][3] = 0.0f;
    result.mat[1][3] = 0.0f;
    result.mat[2][3] = 0.0f;
    result.mat[3][3] = 1.0f;
    return std::move(result);
}

Matrix4x4 Matrix4x4::rotationX(float theta);
Matrix4x4 Matrix4x4::rotationY(float theta);
Matrix4x4 Matrix4x4::rotationZ(float theta);
