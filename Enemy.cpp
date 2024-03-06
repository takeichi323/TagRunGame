#include "Enemy.h"
#include "Engine/Model.h"


//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1)
{
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
    transform_.position_ = XMFLOAT3(0, 0, 10);
   
}

//�X�V
void Enemy::Update()
{
    //transform_.rotate_.z += 5.0f;     // 5������]
}

//�`��
void Enemy::Draw()
{
    //Model::SetTransform(hModel_, transform_);
    //Model::Draw(hModel_);
}

//�J��
void Enemy::Release()
{
}