#include "camera.h"
#include "Direct3D.h"

//�J�������Ǘ����閼�O���
namespace Camera
{
	XMFLOAT3 position_;//�J�����̎��_�i�ʒu�j
	XMFLOAT3 target_;//���Ă�ꏊ�i�œ_�j
	XMMATRIX view_;//�r���[�s��
	XMMATRIX proj_;
	XMMATRIX billBoard_;
}

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	position_ = XMFLOAT3(0, 3, -10);	//�J�����̈ʒu
	target_ = XMFLOAT3( 0, 0, 0);	//�J�����̏œ_

	//�v���W�F�N�V�����s��
	proj_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�r���[�s��
	view_ = XMMatrixLookAtLH(XMVectorSet(position_.x, position_.y, position_.z, 0),
		XMVectorSet(target_.x, target_.y, target_.z, 0), XMVectorSet(0, 1, 0, 0));


	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	billBoard_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&target_)- XMLoadFloat3(&position_), XMVectorSet(0, 1, 0, 0));
	billBoard_ = XMMatrixInverse(nullptr, billBoard_);
}

//�œ_��ݒ�
void Camera::SetTarget(XMFLOAT3 target) { target_ = target; }

//�ʒu��ݒ�
void Camera::SetPosition(XMFLOAT3 position) { position_ = position; }

//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return target_; }

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return position_; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return view_; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix() { return proj_; }

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix(){	return billBoard_; }
