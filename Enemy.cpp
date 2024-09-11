#include "Enemy.h"
#include "Engine/Model.h"
#include "Player.h"
#include <iostream>


//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1),trackingAI_(nullptr),player_(nullptr)
{
}

//デストラクタ
Enemy::~Enemy()
{
    if (trackingAI_)
    {
        delete trackingAI_;
        trackingAI_ = nullptr;

    }

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

    //プレイヤーのオブジェクト取得
    player_ = dynamic_cast<Player*>(GetParent()->FindObject("Player"));
    //AIの初期化
    trackingAI_ = new TrackingAI(this,0.02f);

    //プレイヤーの位置を目的地に設定
    if (player_) {
        trackingAI_->SetDestination(player_->GetPosition());
    }

}

//更新
void Enemy::Update()
{
    if (player_ != nullptr) {
        //プレイヤーの現在位置を取得して目的地として設定
        XMFLOAT3 playerPosition = player_->GetPosition();

        std::cout << "Player position:(" << playerPosition.x << "," << playerPosition.y << "," << playerPosition.z << ")" << std::endl;
        trackingAI_->SetDestination(playerPosition);
    }
    else {
        std::cout << "Player object is null" << std::endl;
    }
        
    if (trackingAI_ != nullptr) {
        //追跡処理の実行
        trackingAI_->Update();
    }
    
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