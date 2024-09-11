#include "TrackingAI.h"
#include "Engine/Model.h"
#include <DirectXMath.h>

using namespace DirectX;

// コンストラクタ
TrackingAI::TrackingAI(GameObject* parent,float speed)
    : parent_(parent), speed_(speed) 
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

    //現在位置の取得
    XMFLOAT3 currentPosition = parent_->GetPosition();
    //VECTOR型に変換
    XMVECTOR currentPositionVec = XMLoadFloat3(&currentPosition);
    XMVECTOR destinationVec = XMLoadFloat3(&destination_);

    //目的地への方向計算
    XMVECTOR directionVec = XMVectorSubtract(destinationVec, currentPositionVec);
    float distance = XMVectorGetX(XMVector3Length(directionVec));

    //移動量の計算
    float moveDistance = min(speed_, distance);//min？
    directionVec = XMVector3Normalize(directionVec);
    XMVECTOR moveVec = XMVectorScale(directionVec, moveDistance);

    //新しい位置を計算
    XMVECTOR newPositionVec = XMVectorAdd(currentPositionVec, moveVec);

    //新しい位置をXMFLOAT3に変換
    XMFLOAT3 newPosition{};
    XMStoreFloat3(&newPosition, newPositionVec);
    parent_->SetPosition(newPosition);

    /*parent_,destination_,speed_の値が読み込めてないので
    　原因と対策を考える*/
    /*ベクトルの長さ（palyerとEnmey間）を求めてその分移動するとか*/

   

}