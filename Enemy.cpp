#include "Enemy.h"
#include "Engine/Model.h"
#include <DirectXMath.h>


//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1)
{
    
}

//デストラクタ
Enemy::~Enemy()
{
}




//初期化
void Enemy::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Enemy.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = XMFLOAT3(3, 0.5, 10);
    transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
   
}

//更新
void Enemy::Update()
{
    //transform_.rotate_.z += 5.0f;     // 5°ずつ回転
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