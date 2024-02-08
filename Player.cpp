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
   
    //�S�̂̃}�b�v���m�F���邽�߂̃J�����ʒu
    Camera::SetPosition(XMFLOAT3(25, 50, -8));
    Camera::SetTarget(XMFLOAT3(25, 10, 10));

    pStage_ = (Stage*)FindObject("Stage");


}

//�X�V
void Player::Update()
{
	prevPosition_ = transform_.position_;
    //�J�����ʒu
     // CameraPosition();
      //Direction();
	  //�}�E�X���쏈��
	  MouseControl();

	  //�J��������
	  CameraMove();
	  

	/*  HitTest();*/
    
   //�E�ړ�
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += PLAYERMOVE;
        //Audio::Play(hSound_);
    }
   //���ړ�
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= PLAYERMOVE;
       // Audio::Stop(hSound_);
    }
    //�O�ړ�
    if (Input::IsKey(DIK_W))
    {
		// �ړ��O�̈ʒu��ۑ�
		/*XMFLOAT3 originalPosition = transform_.position_;*/
		transform_.position_.z += PLAYERMOVE;
		
       
    }
    //��ړ�
    if (Input::IsKey(DIK_S))
    {
		// �ړ��O�̈ʒu��ۑ�
		/*XMFLOAT3 originalPosition = transform_.position_;*/
		transform_.position_.z -= PLAYERMOVE;
		

    }

    
    //�ǂƂ̔���
    int checkX1, checkX2;
    int checkZ1, checkZ2;

    //�E
    {
        checkX1 = (int)(transform_.position_.x + 0.3f);
        checkZ1 = (int)(transform_.position_.z + 0.2f);

        checkX2 = (int)(transform_.position_.x + 0.3f);
        checkZ2 = (int)(transform_.position_.z - 0.2f);

        if (pStage_->IsWall(checkX1, checkZ1) == true ||pStage_->IsWall(checkX2, checkZ2) == true)
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
		POINT mouseCursorPosition;//POINT:x ���W�� y ���W���`
		GetCursorPos(&mouseCursorPosition);

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





