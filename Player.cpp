#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"




//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), hSound_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //�T�E���h�f�[�^�̃��[�h
    hSound_ = Audio::Load("Jazz 1.wav");
    assert(hSound_ >= 0);
}

//�X�V
void Player::Update()
{
    //�J�����ʒu
      CameraPosition();
    
    //�X�y�[�X�L�[��������Ă�����
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += 0.25;
        Audio::Play(hSound_);
    }
    //�X�y�[�X�L�[��������Ă�����
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= 0.25;
        Audio::Stop(hSound_);
    }
}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    
}

//�J��
void Player::Release()
{
}

void Player::CameraPosition()
{
    //1�t���[���̈ړ��x�N�g��
    XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//����0.1��
    //�I�u�W�F�N�g�̌��ݒn���x�N�g���^�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    Camera::SetPosition(transform_.position_);
    XMFLOAT3 camTarget;
    XMStoreFloat3(&camTarget, vPos + vMove);
    Camera::SetTarget(camTarget);
}


