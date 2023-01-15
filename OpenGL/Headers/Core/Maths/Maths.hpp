#pragma once
#include <cmath>
#define PI_NUM 3.141592653589793238462643383279f
#define DEG2RAD PI_NUM/180
namespace Maths
{
    namespace sMatrix
    {
        class Mat3;
        class Mat4;
    }

    namespace sVector
    {
        class Vector4;

        class Vector2
        {
        public:
            //MEMBERS
            float x;
            float y;

            //CONSTRUCTORS
            Vector2(void);
            Vector2(float x, float y);
            Vector2(const Vector2& v);

            //DECONSTRUCTOR
            ~Vector2(void);

            //ASSINGMENT AND EQUALITY OPERATIONS
            Vector2 operator = (const Vector2& v);
            Vector2 operator = (const float& f);
            Vector2 operator - (void);
            bool operator == (const Vector2& v);
            bool operator != (const Vector2& v);

            //VECTOR2 TO VECTOR2 OPERATIONS
            Vector2 operator + (const Vector2& v);
            Vector2 operator - (const Vector2& v);
            Vector2 operator * (const Vector2& v);
            Vector2 operator / (const Vector2& v);

            //VECTOR2 TO THIS OPERATIONS
            Vector2 operator += (const Vector2& v);
            Vector2 operator -= (const Vector2& v);
            Vector2 operator *= (const Vector2& v);
            Vector2 operator /= (const Vector2& v);

            //SCALER TO VECTOR2 OPERATIONS
            Vector2 operator + (float v);
            Vector2 operator - (float v);
            Vector2 operator * (float v);
            Vector2 operator / (float v);

            //SCALER TO THIS OPERATIONS
            Vector2 operator += (float v);
            Vector2 operator -= (float v);
            Vector2 operator *= (float v);
            Vector2 operator /= (float v);
        };
        class Vector3
        {
        public:
            //MEMBERS
            float x;
            float y;
            float z;

            //CONSTRUCTORS
            Vector3(void);
            Vector3(float x);
            Vector3(float x, float y, float z);
            Vector3(const Vector3& v);
            Vector3(const Vector4& v);

            //DECONSTRUCTOR
            ~Vector3(void);

            //UTILS

            float* ToFloat3();

            void Normalize();
            float GetMagnitude();
            //Vector3 GetVector2pts(const Vector3& v, const Vector3& f);
            //Vector3 GetNormal(const Vector3& v, const Vector3& f);
            Vector3 crossProduct(const Vector3& v, const Vector3& f);
            static float dotProduct(const Vector3& v, const Vector3& f);

            //ASSINGMENT AND EQUALITY OPERATIONS
            Vector3 operator = (const Vector3& v);
            Vector3 operator = (const float& f);
            Vector3 operator - (void);
            bool operator == (const Vector3& v);
            bool operator != (const Vector3& v);

            //VECTOR3 TO VECTOR3 OPERATIONS
            Vector3 operator + (const Vector3& v);
            Vector3 operator - (const Vector3& v);
            Vector3 operator * (const Vector3& v);
            Vector3 operator / (const Vector3& v);

            //VECTOR3 TO THIS OPERATIONS
            Vector3 operator += (const Vector3& v);
            Vector3 operator -= (const Vector3& v);
            Vector3 operator *= (const Vector3& v);
            Vector3 operator /= (const Vector3& v);

            //SCALER TO VECTOR3 OPERATIONS
            Vector3 operator + (float v);
            Vector3 operator - (float v);
            Vector3 operator * (float v);
            Vector3 operator / (float v);

            //SCALER TO THIS OPERATIONS
            Vector3 operator += (float v);
            Vector3 operator -= (float v);
            Vector3 operator *= (float v);
            Vector3 operator /= (float v);

            //float operator = (const Vector3 a);
        };
        class Vector4
        {
        public:
            //MEMBERS
            float x;
            float y;
            float z;
            float w;

            //CONSTRUCTORS
            Vector4(void);
            Vector4(float x, float y, float z, float w);
            Vector4(const Vector3& v);
            Vector4(const Vector3& v, float w);
            Vector4(const Vector4& v);

            //DECONSTRUCTOR
            ~Vector4(void);

            //UTILS
            float* ToFloat4();
            #pragma deprecated(Normalise)
            void Normalize();
            Vector4 Homogenize();
            float GetMagnitude();
            float dotProduct(const Vector4& v);

            //ASSINGMENT AND EQUALITY OPERATIONS
            Vector4 operator = (const Vector4& v);
            Vector4 operator = (const float& f);
            Vector4 operator - (void);
            bool operator == (const Vector4& v);
            bool operator != (const Vector4& v);

            //VECTOR4 TO VECTOR4 OPERATIONS
            Vector4 operator + (const Vector4& v);
            Vector4 operator - (const Vector4& v);
            Vector4 operator * (const Vector4& v);
            Vector4 operator / (const Vector4& v);

            //VECTOR4 TO THIS OPERATIONS
            Vector4 operator += (const Vector4& v);
            Vector4 operator -= (const Vector4& v);
            Vector4 operator *= (const Vector4& v);
            Vector4 operator /= (const Vector4& v);

            //SCALER TO VECTOR4 OPERATIONS
            Vector4 operator + (float v);
            Vector4 operator - (float v);
            Vector4 operator * (float v);
            Vector4 operator / (float v);

            //SCALER TO THIS OPERATIONS
            Vector4 operator += (float v);
            Vector4 operator -= (float v);
            Vector4 operator *= (float v);
            Vector4 operator /= (float v);

            //MATRIX TO VECTOR4 OPERATIONS
            Vector4 operator *= (const sMatrix::Mat4 m);

            /*inline Vector4 operator * (sMatrix::Mat4 m) {
                float Vec4[4] = { x, y, z, w };
                float tempVec4[4] = { 0, 0, 0, 0 };
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++)
                        tempVec4[line] += m.data[delta][line] * Vec4[delta];
                }
                return Vector4(tempVec4[0], tempVec4[1], tempVec4[2], tempVec4[3]);
            }*/

            /*inline Vector4 operator = (sMatrix::Mat4 m) {
                float Vec4[4] = { x, y, z, w };
                float tempVec4[4] = { 0, 0, 0, 0 };
                for (int line = 0; line < 4; line++) {
                    for (int delta = 0; delta < 4; delta++)
                        tempVec4[line] += m.data[line][delta] * Vec4[delta];
                }

                x = tempVec4[0]; y = tempVec4[1]; z = tempVec4[2]; w = tempVec4[3];
                return *this;
            }*/

            inline bool operator >= (int v) {
                return (x >= v || y >= v || z >= v || w >= v);
            }
        };
    }
    namespace sMatrix
    {
        // Matrice 3x3
        class Mat3
        {
        public:
            float data[3][3];
            Mat3();
            Mat3(float* p_data, long int sizeOfData);
            void Print(const char* desc);
            Mat3 operator=(Mat3 B);
            Mat3 operator+=(Mat3 B);
            Mat3 operator-=(Mat3 B);
            Mat3 operator*=(Mat3 B);
            Mat3 operator+(Mat3 B);
            Mat3 operator-(Mat3 B);
            Mat3 operator*(Mat3 B);
        };
        // Matrice 4x4
        class Mat4
        {
        public:
            float data[4][4];
            Mat4();
            Mat4(float* p_data, long int sizeOfData);
            void Print(const char* desc);
            Mat4 operator=(float p_newData[16]);
            Mat4 operator=(Mat4 B);
            Mat4 operator+=(Mat4 B);
            Mat4 operator-=(Mat4 B);
            Mat4 operator*=(Mat4 B);
            Mat4 operator+(Mat4 B);
            Mat4 operator-(Mat4 B);
            Mat4 operator*(Mat4 B);
            Mat4 GetIdentity(Mat4 identity);

            void SetPerspective(float aspect, float fov, float far, float near);
            static Mat4 CreateTranslationMatrix(const Maths::sVector::Vector3& t);
            static Mat4 CreateScaleMatrix(const Maths::sVector::Vector3& s);
            static Mat4 CreateXRotationMatrix(float a);
            static Mat4 CreateYRotationMatrix(float a);
            static Mat4 CreateZRotationMatrix(float a);
            static Mat4 CreateTransformMatrix(const Maths::sVector::Vector3& p, const Maths::sVector::Vector3& r, const Maths::sVector::Vector3& s);
            float* GetData();
        };
    }
}