#include "Enemy.h"
#include "Engine/Model.h"
#include "Player.h"


//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1)
{
   /* TrackingAI_->Update();*/
}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化
void Enemy::Initialize()
{
    //スタート位置の設定
    // 移動速度の設定
    
    //モデルデータのロード
    hModel_ = Model::Load("Pacplayer.fbx");
    assert(hModel_ >= 0);

    //初期ポジション
    transform_.position_ = XMFLOAT3(2.0, 0.1, 10.5);
}

//更新
void Enemy::Update()
{
    //if (Player_) {
   //    //Playerの位置情報を取得
   //    Vector3 playerPosition = Player_->GetPosition();
 //   // TrackingAI_->SetDestination(playerPosition);
    //    

    //    TrackingAI_->Update();
    //}

}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
}