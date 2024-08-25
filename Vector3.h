#pragma once
#include <DirectXMath.h>

class Vector3 {
public:
    float x, y, z;

    // コンストラクタ
    Vector3();
    Vector3(float x, float y, float z);

    // ベクトルの加算
    Vector3 operator+(const Vector3& other) const;

    // ベクトルの減算
    Vector3 operator-(const Vector3& other) const;

    // スカラー乗算
    Vector3 operator*(float scalar) const;

    // ベクトルの長さ（大きさ）
    float Length() const;

    // 正規化（長さを1にする）
    Vector3 Normalized() const;

    // XMFLOAT3への変換
    DirectX::XMFLOAT3 ToXMFLOAT3() const;
};
