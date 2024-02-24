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
		
		//�E�B���h�E�ʒu���擾
		RECT lprc;//RECT:������ƉE�����̍��W�ɂ���Ďl�p�`���`
		GetWindowRect(Direct3D::hwnd_, &lprc);

		//�}�E�X�J�[�\���̈ʒu���擾
		POINT mouseCursorPosition{};//POINT:x ���W�� y ���W���`
		mouseCursorPosition.x = lprc.left + Direct3D::GetWindowCenterX();
		mouseCursorPosition.y = lprc.top + Direct3D::GetWindowCenterY();

		SetCursorPos(mouseCursorPosition.x,mouseCursorPosition.y);

		//�}�E�X�J�[�\�����Z�b�g����ʒu
		POINT setMoucePos{};

		//X�̃E�B���h�E���S
		setMoucePos.x = lprc.left + Direct3D::GetWindowCenterX();

		//Y�̃E�B���h�E���S
		setMoucePos.y = lprc.top + Direct3D::GetWindowCenterY();

		//�}�E�X�J�[�\���̈ʒu
		SetCursorPos(setMoucePos.x, setMoucePos.y);
	}
}

void Player::CameraMove()
{
	//�}�E�X���������ꍇ
	if (isMouseControl_)
	{
		//�}�E�X�ƃJ�����̘A��
		transform_.rotate_.y += Input::GetMouseMoveX() * MOUSE_CURSOR_HORIZONTAL_MOVE_SPEED;
		cameraHeight_ += Input::GetMouseMoveY() * MOUSE_CURSOR_VERTICAL_MOVE_SPEED;

		//�J�����̈ʒu�ݒ�
	    //�J�����|�W�V����
		XMFLOAT3 camPos = transform_.position_;

		//�J�����œ_�ʒu
		XMVECTOR camTar = CAMERA_TARGET_POSITION;
		//�v���C���[�̌��������ɃJ�����̏œ_�ʒu��]
		camTar = XMVector3TransformCoord(camTar, playerAngleYMatrix_);

		// XMFLOAT3�^����XMVECTOR�^�ɕϊ�
		XMVECTOR VectorcamPos = XMLoadFloat3(&camPos);
		// XMVECTOR�^���m�̑����Z
		XMVECTOR CameraPositionFocus = XMVectorAdd(VectorcamPos, camTar);
		XMFLOAT3 result{};
		// XMVECTOR�^��XMFLOAT3�^�ɕϊ�
		XMStoreFloat3(&result, CameraPositionFocus);

		//�J�����ʒu�Əœ_��ݒ�ύX
		Camera::SetPosition(camPos);
		Camera::SetTarget(result);

		//SetTarget��XMFLOAT�Ȃ̂�camTar��XMFLOAT�^�ɂ���
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





