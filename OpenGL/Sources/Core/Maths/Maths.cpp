#include "Core/Maths/Maths.hpp"

#include <iostream>
#include <math.h>

/************************\
 *-------VECTOR_2-------*
\************************/
#pragma region Vector2
//CONSTRUCTORS
Maths::sVector::Vector2::Vector2(void) : x(0), y(0)
{

}
Maths::sVector::Vector2::Vector2(float x, float y) : x(x), y(y)
{

}
Maths::sVector::Vector2::Vector2(const Vector2& v) : x(v.x), y(v.y)
{

}

//DESTRUCTOR
Maths::sVector::Vector2::~Vector2(void) {}

//ASSINGMENT AND EQUALITY OPERATIONS
Maths::sVector::Vector2 Maths::sVector::Vector2::operator = (const Vector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator = (const float& f)
{
	x = f;
	y = f;
	return *this;
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator - (void)
{
	x = -x;
	y = -y;
	return *this;
}
bool Maths::sVector::Vector2::operator == (const Vector2& v)
{
	return (x == v.x) && (y == v.y);
}
bool Maths::sVector::Vector2::operator != (const Vector2& v)
{
	return (x != v.x) || (y != v.y);
}

//VECTOR2 TO VECTOR2 OPERATIONS
Maths::sVector::Vector2 Maths::sVector::Vector2::operator + (const Vector2& v)
{
	return Vector2(x + v.x, y + v.y);
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator - (const Vector2& v)
{
	return Vector2(x - v.x, y - v.y);
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator * (const Vector2& v)
{
	return Vector2(x * v.x, y * v.y);
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator / (const Vector2& v)
{
	return Vector2(x / v.x, y / v.y);
}

//VECTOR2 TO THIS OPERATIONS
Maths::sVector::Vector2 Maths::sVector::Vector2::operator += (const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator -= (const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator *= (const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator /= (const Vector2& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

//SCALER TO VECTOR2 OPERATIONS
Maths::sVector::Vector2 Maths::sVector::Vector2::operator + (float v)
{
	return Vector2(x + v, y + v);
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator - (float v)
{
	return Vector2(x - v, y - v);
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator * (float v)
{
	return Vector2(x * v, y * v);
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator / (float v)
{
	return Vector2(x / v, y / v);
}

//SCALER TO THIS OPERATIONS
Maths::sVector::Vector2 Maths::sVector::Vector2::operator += (float v)
{
	x += v;
	y += v;
	return *this;
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator -= (float v)
{
	x -= v;
	y -= v;
	return *this;
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator *= (float v)
{
	x *= v;
	y *= v;
	return *this;
}
Maths::sVector::Vector2 Maths::sVector::Vector2::operator /= (float v)
{
	x /= v;
	y /= v;
	return *this;
}
#pragma endregion Vector2
/************************\
 *-------VECTOR_3-------*
\************************/
#pragma region Vector3
//CONSTRUCTORS
Maths::sVector::Vector3::Vector3(void) : x(0), y(0), z(0)
{

}
Maths::sVector::Vector3::Vector3(float x) : x(x), y(x), z(x)
{

}
Maths::sVector::Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{

}
Maths::sVector::Vector3::Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z)
{

}
Maths::sVector::Vector3::Vector3(const Vector4& v) : x(v.x), y(v.y), z(v.z)
{

}

//DESTRUCTOR
Maths::sVector::Vector3::~Vector3(void)
{

}

//UTILS
void Maths::sVector::Vector3::Normalize()
{
	x /= GetMagnitude();
	y /= GetMagnitude();
	z /= GetMagnitude();
}
Maths::sVector::Vector3 Maths::sVector::Vector3::crossProduct(const Vector3& v, const Vector3& f)
{
	return { v.y * f.z - v.z * f.y, v.z * f.x - v.x * f.z, v.x * f.y - v.y * f.x };
}
float Maths::sVector::Vector3::dotProduct(const Vector3& v, const Vector3& f)
{
	return { v.x * f.x + v.y * f.y + v.z * f.z };
}
float Maths::sVector::Vector3::GetMagnitude()
{
	return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//ASSINGMENT AND EQUALITY OPERATIONS
Maths::sVector::Vector3 Maths::sVector::Vector3::operator = (const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator = (const float& f)
{
	x = f;
	y = f;
	z = f;
	return *this;
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator - (void)
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}
bool Maths::sVector::Vector3::operator == (const Vector3& v)
{
	return (x == v.x) && (y == v.y) && (z == v.z);
}
bool Maths::sVector::Vector3::operator != (const Vector3& v)
{
	return (x != v.x) || (y != v.y) || (z != v.z);
}

//VECTOR3 TO VECTOR3 OPERATIONS
Maths::sVector::Vector3 Maths::sVector::Vector3::operator + (const Vector3& v)
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator - (const Vector3& v)
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator * (const Vector3& v)
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator / (const Vector3& v)
{
	return Vector3(x / v.x, y / v.y, z / v.z);
}

//VECTOR3 TO THIS OPERATIONS
Maths::sVector::Vector3 Maths::sVector::Vector3::operator += (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator -= (const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator *= (const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator /= (const Vector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

//SCALER TO VECTOR3 OPERATIONS
Maths::sVector::Vector3 Maths::sVector::Vector3::operator + (float v)
{
	return Vector3(x + v, y + v, z + v);
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator - (float v)
{
	return Vector3(x - v, y - v, z - v);
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator * (float v)
{
	return Vector3(x * v, y * v, z * v);
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator / (float v)
{
	return Vector3(x / v, y / v, z / v);
}

//SCALER TO THIS OPERATIONS
Maths::sVector::Vector3 Maths::sVector::Vector3::operator += (float v)
{
	x += v;
	y += v;
	z += v;
	return *this;
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator -= (float v)
{
	x -= v;
	y -= v;
	z -= v;
	return *this;
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator *= (float v)
{
	x *= v;
	y *= v;
	z *= v;
	return *this;
}
Maths::sVector::Vector3 Maths::sVector::Vector3::operator /= (float v)
{
	x /= v;
	y /= v;
	z /= v;
	return *this;
}

/*float Maths::sVector::Vector3::operator = (const Vector3 a)
{
	return { this->x * a.x + this->y * a.y + z * a.z };
}*/
#pragma endregion Vector3
/************************\
 *-------VECTOR_4-------*
\************************/
#pragma region Vector4
//CONSTRUCTORS
Maths::sVector::Vector4::Vector4(void) : x(0), y(0), z(0), w(0)
{

}
Maths::sVector::Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{

}
Maths::sVector::Vector4::Vector4(const Vector3& v) : x(v.x), y(v.y), z(v.z), w(0)
{

}
Maths::sVector::Vector4::Vector4(const Vector3& v, float w) : x(v.x), y(v.y), z(v.z), w(w)
{

}
Maths::sVector::Vector4::Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w)
{

}

//DESTRUCTOR
Maths::sVector::Vector4::~Vector4(void) { }

//UTILS

float* Maths::sVector::Vector3::ToFloat3() 
{
	return &x;
}

float* Maths::sVector::Vector4::ToFloat4()
{
	return &x;
}
void Maths::sVector::Vector4::Normalize()
{
	x /= GetMagnitude();
	y /= GetMagnitude();
	z /= GetMagnitude();
	w /= GetMagnitude();
}
Maths::sVector::Vector4 Maths::sVector::Vector4::Homogenize()
{
	if (w == 0)
		return { x, y, z, w };
	return { x / w, y / w, z / w, 1 };
}
float Maths::sVector::Vector4::dotProduct(const Vector4& v)
{
	return { v.x * x + v.y * y + v.z * z + v.w * w };
}
float Maths::sVector::Vector4::GetMagnitude() {
	return (float)sqrt(pow(x / w, 2) + pow(y / w, 2) + pow(z / w, 2));
}

//ASSINGMENT AND EQUALITY OPERATIONS
Maths::sVector::Vector4 Maths::sVector::Vector4::operator = (const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator = (const float& f)
{
	x = f;
	y = f;
	z = f;
	w = f;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator - (void)
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
	return *this;
}
bool Maths::sVector::Vector4::operator == (const Vector4& v)
{
	return (x == v.x) && (y == v.y) && (z == v.z) && (w == v.w);
}
bool Maths::sVector::Vector4::operator != (const Vector4& v)
{
	return (x != v.x) || (y != v.y) || (z != v.z) || (w != v.w);
}

//VECTOR4 TO VECTOR4 OPERATIONS
Maths::sVector::Vector4 Maths::sVector::Vector4::operator + (const Vector4& v)
{
	return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator - (const Vector4& v)
{
	return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator * (const Vector4& v)
{
	return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator / (const Vector4& v)
{
	return Vector4(x / v.x, y / v.y, z / v.z, w / v.w);
}

//VECTOR4 TO THIS OPERATIONS
Maths::sVector::Vector4 Maths::sVector::Vector4::operator += (const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator -= (const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator *= (const Vector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator /= (const Vector4& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator *= (const sMatrix::Mat4 m) {
	float Vec4[4] = { x, y, z, w };
	float tempVec4[4] = { 0, 0, 0, 0 };
	for (int line = 0; line < 4; line++) {
		for (int delta = 0; delta < 4; delta++)
			tempVec4[line] += m.data[line][delta] * Vec4[delta];
	}
	
	x = tempVec4[0]; y = tempVec4[1]; z = tempVec4[2]; w = tempVec4[3];
	return *this;
}
//SCALER TO VECTOR4 OPERATIONS
Maths::sVector::Vector4 Maths::sVector::Vector4::operator + (float v)
{
	return Vector4(x + v, y + v, z + v, w + v);
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator - (float v)
{
	return Vector4(x - v, y - v, z - v, w + v);
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator * (float v)
{
	return Vector4(x * v, y * v, z * v, w + v);
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator / (float v)
{
	return Vector4(x / v, y / v, z / v, w + v);
}

//SCALER TO THIS OPERATIONS
Maths::sVector::Vector4 Maths::sVector::Vector4::operator += (float v)
{
	x += v;
	y += v;
	z += v;
	w += v;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator -= (float v)
{
	x -= v;
	y -= v;
	z -= v;
	w += v;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator *= (float v)
{
	x *= v;
	y *= v;
	z *= v;
	w += v;
	return *this;
}
Maths::sVector::Vector4 Maths::sVector::Vector4::operator /= (float v)
{
	x /= v;
	y /= v;
	z /= v;
	w += v;
	return *this;
}
#pragma endregion Vector4
/************************\
 *-------MATRIX_3-------*
\************************/
#pragma region Mat3
Maths::sMatrix::Mat3::Mat3()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			data[x][y] = 0;
		}
	}
}
Maths::sMatrix::Mat3::Mat3(float* p_data, long int sizeOfData)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			if (x + y * 3 < sizeOfData)  data[x][y] = p_data[x + y * 3];
			else data[x][y] = 0;
		}
	}
}
void Maths::sMatrix::Mat3::Print(const char* desc)
{
	std::cout << desc << std::endl;
	std::cout << "--------------------" << std::endl;
	for (int y = 0; y < 3; y++)
	{
		std::cout << '[';
		for (int x = 0; x < 3; x++)
		{
			std::cout << ' ' << data[x][y] << ' ';
		}
		std::cout << ']' << std::endl;
	}
	std::cout << "Order:" << std::endl;
	std::cout << '[';
	for (int y = 0; y < 9; y++)
	{

		std::cout << ' ' << (*data)[y] << ' ';
	}
	std::cout << ']' << std::endl;
	std::cout << "--------------------" << std::endl;
}
Maths::sMatrix::Mat3 Maths::sMatrix::Mat3::operator=(Mat3 B)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			data[x][y] = B.data[x][y];
		}
	}
	return *this;
}
Maths::sMatrix::Mat3 Maths::sMatrix::Mat3::operator+=(Mat3 B)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			data[x][y] += B.data[x][y];
		}
	}
	return *this;
}
Maths::sMatrix::Mat3 Maths::sMatrix::Mat3::operator-=(Mat3 B)
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			data[x][y] -= B.data[x][y];
		}
	}
	return *this;
}
Maths::sMatrix::Mat3 Maths::sMatrix::Mat3::operator*=(Mat3 B)
{
	Mat3 temp;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			temp.data[x][y] = data[0][y] * B.data[x][0] + data[1][y] * B.data[x][1] + data[2][y] * B.data[x][2];
		}
	}
	*this = temp;
	return *this;
}
Maths::sMatrix::Mat3 Maths::sMatrix::Mat3::operator+(Mat3 B)
{
	Mat3 temp;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			temp.data[x][y] = data[x][y] + B.data[x][y];
		}
	}
	return temp;
}
Maths::sMatrix::Mat3 Maths::sMatrix::Mat3::operator-(Mat3 B)
{
	Mat3 temp;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			temp.data[x][y] = data[x][y] - B.data[x][y];
		}
	}
	return temp;
}
Maths::sMatrix::Mat3 Maths::sMatrix::Mat3::operator*(Mat3 B)
{
	Mat3 temp;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			temp.data[x][y] = data[0][y] * B.data[x][0] + data[1][y] * B.data[x][1] + data[2][y] * B.data[x][2];
		}
	}
	return temp;
}
#pragma endregion Mat3
/************************\
 *-------MATRIX_4-------*
\************************/
#pragma region Mat4
Maths::sMatrix::Mat4::Mat4()
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			data[x][y] = 0;
		}
	}
}
Maths::sMatrix::Mat4::Mat4(float* p_data, long int sizeOfData)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (x + y * 4 < sizeOfData)  data[x][y] = p_data[x + y * 4];
			else data[x][y] = 0;
		}
	}
}
void Maths::sMatrix::Mat4::Print(const char* desc)
{
	std::cout << desc << std::endl;
	std::cout << "--------------------" << std::endl;
	for (int y = 0; y < 4; y++)
	{
		std::cout << '[';
		for (int x = 0; x < 4; x++)
		{
			std::cout << ' ' << data[x][y] << ' ';
		}
		std::cout << ']' << std::endl;
	}
	std::cout << "Order:" << std::endl;
	std::cout << '[';
	for (int y = 0; y < 16; y++)
	{

		std::cout << ' ' << (*data)[y] << ' ';
	}
	std::cout << ']' << std::endl;
	std::cout << "--------------------" << std::endl;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::operator=(float p_newData[16]) 
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (x + y * 4 < 16)  data[x][y] = p_newData[x + y * 4];
			else data[x][y] = 0;
		}
	}
	return *this;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::operator=(Mat4 B)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			data[x][y] = B.data[x][y];
		}
	}
	return *this;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::operator+=(Mat4 B)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			data[x][y] += B.data[x][y];
		}
	}
	return *this;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::operator-=(Mat4 B)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			data[x][y] -= B.data[x][y];
		}
	}
	return *this;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::operator*=(Mat4 B)
{
	Mat4 temp;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			temp.data[x][y] = data[0][y] * B.data[x][0] + data[1][y] * B.data[x][1] + data[2][y] * B.data[x][2] + data[3][y] * B.data[x][3];
		}
	}
	*this = temp;
	return *this;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::operator+(Mat4 B)
{
	Mat4 temp;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			temp.data[x][y] = data[x][y] + B.data[x][y];
		}
	}
	return temp;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::operator-(Mat4 B)
{
	Mat4 temp;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			temp.data[x][y] = data[x][y] - B.data[x][y];
		}
	}
	return temp;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::operator*(Mat4 B)
{
	Mat4 temp;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			temp.data[x][y] = data[0][y] * B.data[x][0] + data[1][y] * B.data[x][1] + data[2][y] * B.data[x][2] + data[3][y] * B.data[x][3];
		}
	}
	return temp;
}
void Maths::sMatrix::Mat4::SetPerspective(float aspect, float fov, float far, float near)
{
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			data[x][y] = 0;
		}
	}
	data[0][0] = 1 / (aspect * tan(fov / 2));
	data[1][1] = 1 / (tan(fov / 2));
	data[2][2] = -((far + near) / (far - near));
	data[2][3] = -((2 * far * near) / (far - near));
	data[3][2] = -1;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::CreateTranslationMatrix(const Maths::sVector::Vector3& t)
{
	Mat4 temp;
	for (int i = 0; i < 4; i++)
		temp.data[i][i] = 1;

	temp.data[3][0] = t.x;
	temp.data[3][1] = t.y;
	temp.data[3][2] = t.z;
	return temp;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::CreateScaleMatrix(const Maths::sVector::Vector3& s)
{
	Mat4 temp;
	for (int i = 0; i < 4; i++)
		temp.data[i][i] = 1;

	temp.data[0][0] = s.x;
	temp.data[1][1] = s.y;
	temp.data[2][2] = s.z;
	return temp;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::CreateXRotationMatrix(float a)
{
	Mat4 temp;
	for (int i = 0; i < 4; i++)
		temp.data[i][i] = 1;

	temp.data[1][1] = cos(a);
	temp.data[2][1] = -sin(a);
	temp.data[1][2] = sin(a);
	temp.data[2][2] = cos(a);
	return temp;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::CreateYRotationMatrix(float a)
{
	Mat4 temp;
	for (int i = 0; i < 4; i++)
		temp.data[i][i] = 1;

	temp.data[0][0] = cos(a);
	temp.data[2][0] = sin(a);
	temp.data[0][2] = -sin(a);
	temp.data[2][2] = cos(a);
	return temp;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::CreateZRotationMatrix(float a)
{
	Mat4 temp;
	for (int i = 0; i < 4; i++)
		temp.data[i][i] = 1;
	temp.data[0][0] = cos(a);
	temp.data[1][0] = -sin(a);
	temp.data[0][1] = sin(a);
	temp.data[1][1] = cos(a);
	return temp;
}
Maths::sMatrix::Mat4 Maths::sMatrix::Mat4::CreateTransformMatrix(const Maths::sVector::Vector3& p, const Maths::sVector::Vector3& r, const Maths::sVector::Vector3& s)
{
	Mat4 translate = CreateTranslationMatrix(p);
	Mat4 rotateX = CreateXRotationMatrix(r.x);
	Mat4 rotateY = CreateYRotationMatrix(r.y);
	Mat4 rotateZ = CreateZRotationMatrix(r.z);
	Mat4 scaling = CreateScaleMatrix(s);

	return translate * rotateX * rotateY * rotateZ * scaling;
}
float* Maths::sMatrix::Mat4::GetData()
{
	return *data;
}
#pragma endregion Mat4