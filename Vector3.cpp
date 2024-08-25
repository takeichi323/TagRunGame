#include "Vector3.h"
#include <cmath> // 数学関数

// デフォルトコンストラクタ
Vector3::Vector3() : x(0), y(0), z(0) {}

// 引数付きコンストラクタ
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

// ベクトルの加算
Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

// ベクトルの減算
Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

// スカラー乗算
Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

// ベクトルの長さ（大きさ）
float Vector3::Length() const {
    return std::sqrt(x * x + y * y + z * z);
}

// 正規化（長さを1にする）
Vector3 Vector3::Normalized() const {
    float len = Length();
    if (len == 0) return Vector3(0, 0, 0); // 長さが0の場合の特別なケース
    return Vector3(x / len, y / len, z / len);
}

// XMFLOAT3への変換
DirectX::XMFLOAT3 Vector3::ToXMFLOAT3() const {
    return DirectX::XMFLOAT3(x, y, z);
}
