#include "Enemy.h"
#include "Engine/Model.h"
#include <DirectXMath.h>


//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1)
{
    
}

struct EnemyPos {
    DirectX::XMFLOAT3 position;
};
struct PlayerPos {
    DirectX::XMFLOAT3 position;
};
DirectX::XMFLOAT3 GetPlayerPosition(const PlayerPos& player) {
    return player.position;
}

DirectX::XMFLOAT3 GetEnemyPosition(const EnemyPos& enemy) {
    return enemy.position;
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

void EnemyChasePlayer(Enemy& enemy, const PlayerPos& player, float speed) {
    DirectX::XMFLOAT3 playerPosition = GetPlayerPosition(player);
    DirectX::XMFLOAT3 enemyPosition = GetEnemyPosition(enemy);

    // プレイヤーの位置に向かって敵を移動させる
    DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(
        DirectX::XMLoadFloat3(&playerPosition),
        DirectX::XMLoadFloat3(&enemyPosition)
    );
    direction = DirectX::XMVector3Normalize(direction);

    DirectX::XMVECTOR movement = DirectX::XMVectorScale(direction, speed);
    DirectX::XMStoreFloat3(&enemy.position, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&enemyPosition), movement));
}



//開放
void Enemy::Release()
{
}