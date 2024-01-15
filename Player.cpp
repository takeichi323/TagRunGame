#include "Player.h"
#include"Stage.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"


//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), hSound_(-1),pStage_(nullptr)
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
    hModel_ = Model::Load("Pacplayer.fbx");
    assert(hModel_ >= 0);

    //�T�E���h�f�[�^�̃��[�h
    hSound_ = Audio::Load("Jazz 1.wav");
    assert(hSound_ >= 0);

    //���|�W�V����
    transform_.position_.y += 0.5;
	transform_.position_.x += 0.5;
	transform_.position_.z += 1.5;
	
   
	pStage_ = (Stage*)FindObject("Stage");
}

//�X�V
void Player::Update()
{
	prevPosition_ = transform_.position_;
    //�J�����ʒu
      CameraPosition();
      //Direction();

	/*  HitTest();*/
    
    //�X�y�[�X�L�[��������Ă�����
    if (Input::IsKey(DIK_D))
    {
		// �ړ��O�̈ʒu��ۑ�
		/*XMFLOAT3 originalPosition = transform_.position_;*/
		transform_.position_.x += PLAYERMOVE;
       // Audio::Play(hSound_);
		
	
		
    }
    //�X�y�[�X�L�[��������Ă�����
    if (Input::IsKey(DIK_A))
    {
		// �ړ��O�̈ʒu��ۑ�
		/*XMFLOAT3 originalPosition = transform_.position_;*/
		transform_.position_.x -= PLAYERMOVE;
       // Audio::Stop(hSound_);
		
    }
    if (Input::IsKey(DIK_W))
    {
		// �ړ��O�̈ʒu��ۑ�
		/*XMFLOAT3 originalPosition = transform_.position_;*/
		transform_.position_.z += PLAYERMOVE;
		
       
    }
    if (Input::IsKey(DIK_S))
    {
		// �ړ��O�̈ʒu��ۑ�
		/*XMFLOAT3 originalPosition = transform_.position_;*/
		transform_.position_.z -= PLAYERMOVE;
		

    }

	//�ǂƂ̔���
	//int checkX1, checkX2;
	//int checkZ1, checkZ2;
	////�E
	//{
	//	checkX1 = (int)(transform_.position_.x + 0.3f);
	//	checkZ1 = (int)(transform_.position_.z + 0.2f);

	//	checkX2 = (int)(transform_.position_.x + 0.3f);
	//	checkZ2 = (int)(transform_.position_.z - 0.2f);
	//	if (pStage_->IsWall(checkX1, checkZ1) == true || pStage_->IsWall(checkX2, checkZ2) == true)
	//	{
	//		transform_.position_.x = (float)((int)prevPosition_.x) + 1.0f - 0.3;
	//	}
	//}

	////��
	//{
	//	checkX1 = (int)(transform_.position_.x - 0.3f);
	//	checkZ1 = (int)(transform_.position_.z + 0.1f);
	//	checkX2 = (int)(transform_.position_.x - 0.3f);
	//	checkZ2 = (int)(transform_.position_.z - 0.1f);

	//	if (pStage_->IsWall(checkX1, checkZ1) == true || pStage_->IsWall(checkX2, checkZ2) == true)
	//	{
	//		transform_.position_.x = (float)((int)prevPosition_.x) + 0.3;
	//	}

	//}

	////�O
	//{
	//	checkX1 = (int)(transform_.position_.x + 0.1f);
	//	checkZ1 = (int)(transform_.position_.z + 0.3f);
	//	checkX2 = (int)(transform_.position_.x - 0.1f);
	//	checkZ2 = (int)(transform_.position_.z + 0.3f);

	//	if (pStage_->IsWall(checkX1, checkZ1) == true ||pStage_->IsWall(checkX2, checkZ2) == true)
	//	{
	//		transform_.position_.z = (float)((int)prevPosition_.z) + 1.0f - 0.3;
	//	}
	//}

	////��
	//{
	//	checkX1 = (int)(transform_.position_.x + 0.1f);
	//	checkZ1 = (int)(transform_.position_.z - 0.3f);
	//	checkX2 = (int)(transform_.position_.x - 0.1f);
	//	checkZ2 = (int)(transform_.position_.z - 0.3f);

	//	if (pStage_->IsWall(checkX1, checkZ1) == true ||pStage_->IsWall(checkX2, checkZ2) == true)
	//	{
	//		transform_.position_.z = (float)((int)prevPosition_.z) + 0.3;
	//	}
	//}

	//transform_.rotate_.y = XMConvertToDegrees(angle);

	
    
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

//�J�����ʒu(��l��)
void Player::CameraPosition()
{
    //1�t���[���̈ړ��x�N�g��
   // XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//����0.1��
    //�I�u�W�F�N�g�̌��ݒn���x�N�g���^�ɕϊ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    Camera::SetPosition(transform_.position_);
    XMFLOAT3 camTarget;
    XMStoreFloat3(&camTarget, vPos + vMove);
    Camera::SetTarget(camTarget);
}



bool Player::WallHitTest()
{

	// Player�N���X����Stage�N���X�ւ̎Q�Ƃ��擾
	Stage* stage = dynamic_cast<Stage*>(GetParent()->FindChildObject("Stage"));
	//�����擾�ł����ꍇ
	if (stage)
	{
		// Player�̈ʒu���X�e�[�W���W�n�ɕϊ����L���X�g���Ă�[��
		int playerX = static_cast<int>(transform_.position_.x);
		int playerZ = static_cast<int>(transform_.position_.z);
		// �X�e�[�W��̍��W���ǂ��ǂ������`�F�b�N
		if (stage->IsWall(playerX, playerZ))
		{
			// �ǂƓ������Ă���ꍇ��true��Ԃ�
			return true;
		}
	}
	//�������Ă��Ȃ��ꍇfalse��Ԃ�
	return false;
	
}





