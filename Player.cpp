#include "Player.h"
#include"Stage.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/Transform.h"





//�萔
static const float MOUSE_CURSOR_HORIZONTAL_MOVE_SPEED = 0.1f;				//�}�E�X��X���ړ��̑���
static const float MOUSE_CURSOR_VERTICAL_MOVE_SPEED = 0.01f;				//�}�E�X��Y���ړ��̑���
static const XMVECTOR CAMERA_TARGET_POSITION = XMVectorSet(0, 0, 5, 0);		//�J�����̏œ_

using namespace DirectX;


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
	  //�}�E�X���쏈��
	  MouseControl();
	  //�J��������
	  CameraMove();
	  //�v���C���[�ړ�����
	  PlayerKeyMove();
	 
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






//�^�ϊ��̂��߂ɕK�v�Ȋ֐�
XMFLOAT3 Player::XMVectorToXMFLOAT3(const XMVECTOR& vector)
{
	XMFLOAT3 result;
	XMStoreFloat3(&result, vector);
	return result;
}


//�}�E�X����̏���
void Player::MouseControl()
{
	//�����}�E�X���삪���ꂽ��
	if (isMouseControl_)
	{
		RECT lprc{};
		// �}�E�X�̓����Ɋ�Â��ăv���C���[�̃J�����̊p�x���X�V
		float mouseX = Input::GetMouseMoveX();
		float mouseY = Input::GetMouseMoveY();
		transform_.rotate_.y += mouseX * MOUSE_CURSOR_HORIZONTAL_MOVE_SPEED;
		cameraHeight_ += mouseY * MOUSE_CURSOR_VERTICAL_MOVE_SPEED;

		// �}�E�X�J�[�\���̈ʒu���E�B���h�E�̒��S�ɖ߂�
		POINT windowCenter{};
		windowCenter.x = lprc.left + (lprc.right - lprc.left) / 2;
		windowCenter.y = lprc.top + (lprc.bottom - lprc.top) / 2;
		SetCursorPos(windowCenter.x, windowCenter.y);
	}
}

void Player::CameraMove()
{
	//�}�E�X���������ꍇ
	if (isMouseControl_)
	{
		// �v���C���[�̃J�����̊p�x����ɃJ�����̈ʒu�Əœ_��ݒ�
		float radius = 5.0f; // �J�����̔��a
		float camPosX = radius * sin(transform_.rotate_.y);
		float camPosZ = radius * cos(transform_.rotate_.y);
		float camPosY = transform_.position_.y + cameraHeight_;
		XMFLOAT3 camPos(camPosX, camPosY, camPosZ);
		XMFLOAT3 camTarget(transform_.position_.x, transform_.position_.y, transform_.position_.z);

		// �J�����ʒu�Əœ_��ݒ�
		Camera::SetPosition(camPos);
		Camera::SetTarget(camTarget);
	}
}

//�v���C���[�����ʒu
void Player::PlayerInitialPosition()
{


}



void Player::PlayerKeyMove()
{
	
	if (Input::IsKey(DIK_D))
	{	
		transform_.position_.x += PLAYERMOVE;
		// Audio::Play(hSound_);
	}
	
	if (Input::IsKey(DIK_A))
	{
		transform_.position_.x -= PLAYERMOVE;
		// Audio::Stop(hSound_);
	}
	if (Input::IsKey(DIK_W))
	{
		transform_.position_.z += PLAYERMOVE;
	}
	if (Input::IsKey(DIK_S))
	{
		transform_.position_.z -= PLAYERMOVE;
	}
	
}





