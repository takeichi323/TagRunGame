#include "camera.h"
#include "Direct3D.h"

//カメラを管理する名前空間
namespace Camera
{
	XMFLOAT3 position_;//カメラの視点（位置）
	XMFLOAT3 target_;//見てる場所（焦点）
	XMMATRIX view_;//ビュー行列
	XMMATRIX proj_;
	XMMATRIX billBoard_;
}

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	position_ = XMFLOAT3(0, 3, -10);	//カメラの位置
	target_ = XMFLOAT3( 0, 0, 0);	//カメラの焦点

	//プロジェクション行列
	proj_ = XMMatrixPerspectiveFovLH(XM_PIDIV4, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//ビュー行列
	view_ = XMMatrixLookAtLH(XMVectorSet(position_.x, position_.y, position_.z, 0),
		XMVectorSet(target_.x, target_.y, target_.z, 0), XMVectorSet(0, 1, 0, 0));


	//ビルボード行列
	//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	billBoard_ = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&target_)- XMLoadFloat3(&position_), XMVectorSet(0, 1, 0, 0));
	billBoard_ = XMMatrixInverse(nullptr, billBoard_);
}

//焦点を設定
void Camera::SetTarget(XMFLOAT3 target) { target_ = target; }

//位置を設定
void Camera::SetPosition(XMFLOAT3 position) { position_ = position; }

//焦点を取得
XMFLOAT3 Camera::GetTarget() { return target_; }

//位置を取得
XMFLOAT3 Camera::GetPosition() { return position_; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return view_; }

//プロジェクション行列を取得
XMMATRIX Camera::GetProjectionMatrix() { return proj_; }

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix(){	return billBoard_; }
