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
void TrackingAI::SetDestination(const Vector3& destination) {
    destination_ = destination;
}

// 目的地に向かって移動する
void TrackingAI::Update() {
    if (parent_ == nullptr) return;


    Vector3 currentPosition = parent_->GetPosition();
    Vector3 direction = (destination_ - currentPosition).Normalized();
    Vector3 newPosition = currentPosition + direction * speed_;

    parent_->SetPosition(newPosition);
}