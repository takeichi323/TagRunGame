#include "Player.h"
#include"Stage.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/Transform.h"





//定数
static const float MOUSE_CURSOR_HORIZONTAL_MOVE_SPEED = 0.1f;				//マウスのX軸移動の速さ
static const float MOUSE_CURSOR_VERTICAL_MOVE_SPEED = 0.01f;				//マウスのY軸移動の速さ
static const XMVECTOR CAMERA_TARGET_POSITION = XMVectorSet(0, 0, 5, 0);		//カメラの焦点

using namespace DirectX;


//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), hSound_(-1),pStage_(nullptr)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Pacplayer.fbx");
    assert(hModel_ >= 0);

    //サウンドデータのロード
    hSound_ = Audio::Load("Jazz 1.wav");
    assert(hSound_ >= 0);

    //仮ポジション
    transform_.position_.y += 0.5;
	transform_.position_.x += 0.5;
	transform_.position_.z += 1.5;
	
   
	pStage_ = (Stage*)FindObject("Stage");
}

//更新
void Player::Update()
{ 
	  //マウス操作処理
	  MouseControl();
	  //カメラ処理
	  CameraMove();
	  //プレイヤー移動処理
	  PlayerKeyMove();
	 
}

//描画
void Player::Draw()
{
   
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    
}

//開放
void Player::Release()
{
}






//型変換のために必要な関数
XMFLOAT3 Player::XMVectorToXMFLOAT3(const XMVECTOR& vector)
{
	XMFLOAT3 result;
	XMStoreFloat3(&result, vector);
	return result;
}


//マウス操作の処理
void Player::MouseControl()
{
	//もしマウス操作がされたら
	if (isMouseControl_)
	{
		RECT lprc{};
		// マウスの動きに基づいてプレイヤーのカメラの角度を更新
		float mouseX = Input::GetMouseMoveX();
		float mouseY = Input::GetMouseMoveY();
		transform_.rotate_.y += mouseX * MOUSE_CURSOR_HORIZONTAL_MOVE_SPEED;
		cameraHeight_ += mouseY * MOUSE_CURSOR_VERTICAL_MOVE_SPEED;

		// マウスカーソルの位置をウィンドウの中心に戻す
		POINT windowCenter{};
		windowCenter.x = lprc.left + (lprc.right - lprc.left) / 2;
		windowCenter.y = lprc.top + (lprc.bottom - lprc.top) / 2;
		SetCursorPos(windowCenter.x, windowCenter.y);
	}
}

void Player::CameraMove()
{
	//マウスが動いた場合
	if (isMouseControl_)
	{
		// プレイヤーのカメラの角度を基にカメラの位置と焦点を設定
		float radius = 5.0f; // カメラの半径
		float camPosX = radius * sin(transform_.rotate_.y);
		float camPosZ = radius * cos(transform_.rotate_.y);
		float camPosY = transform_.position_.y + cameraHeight_;
		XMFLOAT3 camPos(camPosX, camPosY, camPosZ);
		XMFLOAT3 camTarget(transform_.position_.x, transform_.position_.y, transform_.position_.z);

		// カメラ位置と焦点を設定
		Camera::SetPosition(camPos);
		Camera::SetTarget(camTarget);
	}
}

//プレイヤー初期位置
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





