#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/BoxCollider.h"


//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), hSound_(-1), pStage_(nullptr)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    
    //�����蔻��̃T�C�Y
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
    AddCollider(collision);

    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Pacplayer.fbx");
    assert(hModel_ >= 0);

    //�T�E���h�f�[�^�̃��[�h
    hSound_ = Audio::Load("Jazz 1.wav");
    assert(hSound_ >= 0);

    //���|�W�V����
    //Player_Transform.position_.y += 0.5;
    Player_Transform.position_ = XMFLOAT3(1.0, 0.5, 1.5);
    //Player_Transform.position_ = XMFLOAT3(10.5, 5.0, 1.5);
   
    //�S�̂̃}�b�v���m�F���邽�߂̃J�����ʒu
    Camera::SetPosition(XMFLOAT3(25, 50, -8));
    Camera::SetTarget(XMFLOAT3(25, 10, 10));

    pStage_ = (Stage*)FindObject("Stage");


}

//�X�V
void Player::Update()
{
    prevPosition_ = Player_Transform.position_;
    //�J�����ʒu
     CameraPosition();
    
   //�E�ړ�
    if (Input::IsKey(DIK_D))
    {
        Player_Transform.position_.x += PLAYERMOVE;
       // Audio::Play(hSound_);
    }
   //���ړ�
    if (Input::IsKey(DIK_A))
    {
        Player_Transform.position_.x -= PLAYERMOVE;
       // Audio::Stop(hSound_);
    }
    //�O�ړ�
    if (Input::IsKey(DIK_W))
    {
        Player_Transform.position_.z += PLAYERMOVE;
       
    }
    //��ړ�
    if (Input::IsKey(DIK_S))
    {
        Player_Transform.position_.z -= PLAYERMOVE;

    }


    //�ǂƂ̔���
    int checkX1, checkX2;
    int checkZ1, checkZ2;

    //�E
    {
        checkX1 = (int)(Player_Transform.position_.x + 0.3f);
        checkZ1 = (int)(Player_Transform.position_.z + 0.2f);

        checkX2 = (int)(Player_Transform.position_.x + 0.3f);
        checkZ2 = (int)(Player_Transform.position_.z - 0.2f);

        if (pStage_->IsWall(checkX1, checkZ1) == true ||pStage_->IsWall(checkX2, checkZ2) == true)
        {
            Player_Transform.position_.x = (float)((int)prevPosition_.x) + 1.0f - 0.3;
        }
    }

    //��
    {
        checkX1 = (int)(Player_Transform.position_.x - 0.3f);
        checkZ1 = (int)(Player_Transform.position_.z + 0.1f);

        checkX2 = (int)(Player_Transform.position_.x - 0.3f);
        checkZ2 = (int)(Player_Transform.position_.z - 0.1f);

        if (pStage_->IsWall(checkX1, checkZ1) == true ||
            pStage_->IsWall(checkX2, checkZ2) == true)
        {
            Player_Transform.position_.x = (float)((int)prevPosition_.x) + 0.3;
        }
    }

    //��
    /*{
        checkX1 = (int)(Player_Transform.position_.x + 0.1f);
        checkZ1 = (int)(Player_Transform.position_.z + 0.3f);

        checkX2 = (int)(Player_Transform.position_.x - 0.1f);
        checkZ2 = (int)(Player_Transform.position_.z + 0.3f);

        if (pStage_->IsWall(checkX1, checkZ1) == true ||
            pStage_->IsWall(checkX2, checkZ2) == true)
        {
            Player_Transform.position_.z = (float)((int)prevPosition_.z) + 1.0f - 0.3;
        }
    }*/

    //��O
    {
        checkX1 = (int)(Player_Transform.position_.x + 0.1f);
        checkZ1 = (int)(Player_Transform.position_.z - 0.3f);

        checkX2 = (int)(Player_Transform.position_.x - 0.1f);
        checkZ2 = (int)(Player_Transform.position_.z - 0.3f);

        if (pStage_->IsWall(checkX1, checkZ1) == true ||
            pStage_->IsWall(checkX2, checkZ2) == true)
        {
            Player_Transform.position_.z = (float)((int)prevPosition_.z) + 0.3;
        }
    }


    
   
}

//�`��
void Player::Draw()
{
   
    Model::SetTransform(hModel_, Player_Transform);
    Model::Draw(hModel_);

    
}

//�J��
void Player::Release()
{
}

//�J�����ʒu(��l��)
void Player::CameraPosition()
{
    // �J�����̎����x�N�g�����擾
    XMVECTOR vecSightline = /*�J�����̈ʒu�[�J�����œ_*/;

    // �}�E�X�̏����擾
    XMFLOAT3 mouseMove = /*Input����擾�����ړ���xy*/;

    // �}�E�X�Ŏ擾�����ړ��ʂ����Ƃɉ�]�s��𐶐�
    XMMATRIX matRotate = XMMatrixRotationY(/*�p�x*/);
    XMVector3Transform(vecSightline, matRotate);

    // �����x�N�g���𐳋K����A��]�s��Ńx�N�g������]
    /*���K���������x�N�g��*/ = XMVector3Normalize(/*���K���������x�N�g��*/);


    // �x�N�g�����^�[�Q�b�g�ɃZ�b�g
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos,/*�����x�N�g��*/)
    
    // �J�����̈ʒu���v���C���[�|�W�V�����ōX�V
}





