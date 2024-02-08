#include "Enemy.h"
#include "Engine/Model.h"
#include <DirectXMath.h>


//�R���X�g���N�^
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


//�f�X�g���N�^
Enemy::~Enemy()
{
}




//������
void Enemy::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Enemy.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = XMFLOAT3(3, 0.5, 10);
    transform_.scale_ = XMFLOAT3(0.5f, 0.5f, 0.5f);
   
}

//�X�V
void Enemy::Update()
{
    //transform_.rotate_.z += 5.0f;     // 5������]
}

//�`��
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void EnemyChasePlayer(Enemy& enemy, const PlayerPos& player, float speed) {
    DirectX::XMFLOAT3 playerPosition = GetPlayerPosition(player);
    DirectX::XMFLOAT3 enemyPosition = GetEnemyPosition(enemy);

    // �v���C���[�̈ʒu�Ɍ������ēG���ړ�������
    DirectX::XMVECTOR direction = DirectX::XMVectorSubtract(
        DirectX::XMLoadFloat3(&playerPosition),
        DirectX::XMLoadFloat3(&enemyPosition)
    );
    direction = DirectX::XMVector3Normalize(direction);

    DirectX::XMVECTOR movement = DirectX::XMVectorScale(direction, speed);
    DirectX::XMStoreFloat3(&enemy.position, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&enemyPosition), movement));
}



//�J��
void Enemy::Release()
{
}