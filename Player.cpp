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
	//transform_.position_.y += 0.5;
	transform_.position_ = XMFLOAT3(1.0, 0.5, 1.5);
	//transform_.position_ = XMFLOAT3(10.5, 5.0, 1.5);
   
	//�S�̂̃}�b�v���m�F���邽�߂̃J�����ʒu
	Camera::SetPosition(XMFLOAT3(25, 50, -8));
	Camera::SetTarget(XMFLOAT3(25, 10, 10));

	pStage_ = (Stage*)FindObject("Stage");


}


//�X�V
void Player::Update()
{
	
	//�J�����ʒu
	CameraPosition();
	PlayerMove();

	
	

	//�ǂƂ̔���
	int checkX1, checkX2;
	int checkZ1, checkZ2;

	//�E
	{
		checkX1 = (int)(transform_.position_.x + 0.3f);
		checkZ1 = (int)(transform_.position_.z + 0.2f);

		checkX2 = (int)(transform_.position_.x + 0.3f);
		checkZ2 = (int)(transform_.position_.z - 0.2f);

		if (pStage_->IsWall(checkX1, checkZ1) == true || pStage_->IsWall(checkX2, checkZ2) == true)
		{
			transform_.position_.x = (float)((int)prevPosition_.x) + 1.0f - 0.3;
		}
	}

	//��
	{
		checkX1 = (int)(transform_.position_.x - 0.3f);
		checkZ1 = (int)(transform_.position_.z + 0.1f);

		checkX2 = (int)(transform_.position_.x - 0.3f);
		checkZ2 = (int)(transform_.position_.z - 0.1f);

		if (pStage_->IsWall(checkX1, checkZ1) == true ||
			pStage_->IsWall(checkX2, checkZ2) == true)
		{
			transform_.position_.x = (float)((int)prevPosition_.x) + 0.3;
		}
	}

	//��
	{
		checkX1 = (int)(transform_.position_.x + 0.1f);
		checkZ1 = (int)(transform_.position_.z + 0.3f);

		checkX2 = (int)(transform_.position_.x - 0.1f);
		checkZ2 = (int)(transform_.position_.z + 0.3f);

		if (pStage_->IsWall(checkX1, checkZ1) == true ||
			pStage_->IsWall(checkX2, checkZ2) == true)
		{
			transform_.position_.z = (float)((int)prevPosition_.z) + 1.0f - 0.3;
		}
	}

	//��O
	{
		checkX1 = (int)(transform_.position_.x + 0.1f);
		checkZ1 = (int)(transform_.position_.z - 0.3f);

		checkX2 = (int)(transform_.position_.x - 0.1f);
		checkZ2 = (int)(transform_.position_.z - 0.3f);

		if (pStage_->IsWall(checkX1, checkZ1) == true ||
			pStage_->IsWall(checkX2, checkZ2) == true)
		{
			transform_.position_.z = (float)((int)prevPosition_.z) + 0.3;
		}
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

// XMVECTOR����XMFLOAT3�ւ̕ϊ��֐�
XMFLOAT3 XMVectorToXMFLOAT3(const XMVECTOR& vector)
{
	XMFLOAT3 result;
	XMStoreFloat3(&result, vector);
	return result;
}

//�J�����ʒu(��l��)
void Player::CameraPosition()
{

	//1�t���[���̈ړ��x�N�g��
	XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//����0.1��
	// transform_.rotate_.y�x��]������s����쐬
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	//�J�����̑��Έʒu
	XMVECTOR vCamRelative = { 0,5,-10,0 };
	//�J�����̑��Έʒu���v���C���[�̉�]�s��ŕϊ�
	vCamRelative = XMVector3Transform(vCamRelative, mRotY);
	//�J�����̍ŏI�I�Ȉʒu���v�Z
	XMVECTOR vCamPos = vPos + vCamRelative;

	// XMVECTOR����XMFLOAT3�֕ϊ�
	XMFLOAT3 camPos;
	camPos = XMVectorToXMFLOAT3(vCamPos);


	//�J�����̈ʒu��ݒ�
	Camera::SetTarget(transform_.position_);
	Camera::SetPosition(camPos);


	/*XMFLOAT3 camPos = transform_.position_;
	Camera::SetTarget(transform_.position_);
	camPos.y += 5;
	camPos.z -= 10;
	Camera::SetPosition(camPos);*/


	//Camera::SetTarget(transform_.position_);
	////XMVECTOR vCam = { 0,5,-10,0 };
	//vCam = XMVector3TransformCoord(vCam, mRotY);
	//XMStoreFloat3(&camPos, vPos + vCam);
	//Camera::SetPosition(camPos);



	////�I�u�W�F�N�g�̌��ݒn���x�N�g���^�ɕϊ�
	//XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	//Camera::SetPosition(transform_.position_);
	//XMFLOAT3 camTarget;
	//XMStoreFloat3(&camTarget, vPos + vMove);
	//Camera::SetTarget(camTarget);
}

//�v���C���[�̈ړ�
void Player::PlayerMove()
{
	prevPosition_ = transform_.position_;
	XMFLOAT3 move{ 0,0,0 };

	//�E�ړ�
	if (Input::IsKey(DIK_D))
	{
		move.x += PLAYERMOVE;
		// Audio::Play(hSound_);
	}
	//���ړ�
	if (Input::IsKey(DIK_A))
	{
		move.x -= PLAYERMOVE;
		// Audio::Stop(hSound_);
	}
	//�O�ړ�
	if (Input::IsKey(DIK_W))
	{
		move.z += PLAYERMOVE;

	}
	//��ړ�
	if (Input::IsKey(DIK_S))
	{
		move.z -= PLAYERMOVE;

	}

	//�_�b�V���{�^��:���V�t�g
	if (Input::IsKey(DIK_LSHIFT))
	{
		move.x *= DASHPLAYERMOVE;
		move.z *= DASHPLAYERMOVE;

	}

	if (Input::IsKey(DIK_M))
	{
		transform_.rotate_.y += 1.0f; ;
	}
	if (Input::IsKey(DIK_N))
	{
		transform_.rotate_.y -= 1.0f;
	}

	transform_.position_ = transform_.position_ + move;
}







