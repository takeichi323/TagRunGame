#include "TrackingAI.h"
#include "Engine/Model.h"

// コンストラクタ
TrackingAI::TrackingAI(GameObject* parent)
    : parent_(parent), speed_(5.0f) // 例として速度を5.0に設定
{
}

// デストラクタ
TrackingAI::~TrackingAI() {}

// 目的地を設定する
void TrackingAI::SetDestination(const XMFLOAT3& destination) {
    destination_ = destination;
}

// 目的地に向かって移動する
void TrackingAI::Update() {
    if (parent_ == nullptr) return;

    /*Vector3 currentPosition = parent_->GetPosition();
    Vector3 direction = (destination_ - currentPosition).Normalized();
    Vector3 newPosition = currentPosition + direction * speed_;

    parent_->SetPosition(newPosition);*/


    XMFLOAT3 currentPosition = parent_->GetPosition();
    XMVECTOR currentPositionVec = XMLoadFloat3(&currentPosition);
    XMVECTOR destinationVec = XMLoadFloat3(&destination_);

    // destination_ - currentPosition を計算
    XMVECTOR directionVec = XMVectorSubtract(destinationVec, currentPositionVec);
    // Normalized() の代わりに XMVector3Normalize を使用
    directionVec = XMVector3Normalize(directionVec);
    // direction * speed_ を計算
    XMVECTOR speedVec = XMVectorScale(directionVec, speed_);
    // currentPosition + direction * speed_ を計算
    XMVECTOR newPositionVec = XMVectorAdd(currentPositionVec, speedVec);
    // 結果を XMFLOAT3 に格納
    XMFLOAT3 newPosition;
    XMStoreFloat3(&newPosition, newPositionVec);

}