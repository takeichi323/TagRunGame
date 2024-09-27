#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Player.h"
#include "Stage.h"
#include <iostream>

/*
　・壁を認識して壁に当たらずに追跡できるようにする
  ・足音を鳴らすので最初はEnemyが移動している最中に音が出るようにする
  　→最終的には立体的に鳴らす。
   */


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
    //Enemy初期ポジション
    transform_.position_ = XMFLOAT3(2.0, 0.1, 10.5);
}

//更新
void Enemy::Update()
{
    //プレイヤーのオブジェクト取得
    player_ = dynamic_cast<Player*>(GetParent()->FindObject("Player"));

    //AIの初期化
    trackingAI_ = new TrackingAI(this, ENEMYMOVE);

    if (player_ != nullptr) {
        //プレイヤーの現在位置を取得して目的地として設定
        XMFLOAT3 playerPosition = player_->GetPosition();

        //EnemyがPlayerの位置を取得できたかどうかの確認
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
    // 衝突判定を呼び出す
   // CollisionDetection();
    
}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//衝突判定
void Enemy::CollisionDetection()
{
    // 壁との判定のための座標
    int checkX1, checkX2;
    int checkZ1, checkZ2;

    // 壁の衝突判定（右方向）
    checkX1 = (int)(transform_.position_.x + 0.3f);
    checkZ1 = (int)(transform_.position_.z + 0.2f);

    checkX2 = (int)(transform_.position_.x + 0.3f);
    checkZ2 = (int)(transform_.position_.z - 0.2f);

    if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))
    {
        // 右側に壁がある場合、少し左に戻す
        transform_.position_.x -= 0.1f;
    }

    // 左方向
    checkX1 = (int)(transform_.position_.x - 0.3f);
    checkZ1 = (int)(transform_.position_.z + 0.1f);

    checkX2 = (int)(transform_.position_.x - 0.3f);
    checkZ2 = (int)(transform_.position_.z - 0.1f);

    if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))
    {
        // 左側に壁がある場合、少し右に戻す
        transform_.position_.x += 0.1f;
    }

    // 奥方向
    checkX1 = (int)(transform_.position_.x + 0.1f);
    checkZ1 = (int)(transform_.position_.z + 0.3f);

    checkX2 = (int)(transform_.position_.x - 0.1f);
    checkZ2 = (int)(transform_.position_.z + 0.3f);

    if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))
    {
        // 奥に壁がある場合、少し手前に戻す
        transform_.position_.z -= 0.1f;
    }

    // 手前方向
    checkX1 = (int)(transform_.position_.x + 0.1f);
    checkZ1 = (int)(transform_.position_.z - 0.3f);

    checkX2 = (int)(transform_.position_.x - 0.1f);
    checkZ2 = (int)(transform_.position_.z - 0.3f);

    if (pStage_->IsWall(checkX1, checkZ1) || pStage_->IsWall(checkX2, checkZ2))
    {
        // 手前に壁がある場合、少し奥に戻す
        transform_.position_.z += 0.1f;
    }
}

//プレイヤー方向の計算
XMFLOAT3 Enemy::CalculateDirectionToPlayer(const XMFLOAT3& playerPosition)
{
   // プレイヤーまでのベクトルを計算
    XMFLOAT3 direction{};
    direction.x = playerPosition.x - transform_.position_.x;
    direction.y = playerPosition.y - transform_.position_.y;
    direction.z = playerPosition.z - transform_.position_.z;

     // ベクトルを正規化（方向のみを保持し、距離を1にする）
      float length = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
      if (length != 0) {
         direction.x /= length;
         direction.y /= length;
         direction.z /= length;
      }

      return direction;
}

//開放
void Enemy::Release()
{
}