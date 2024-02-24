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
		
		//ウィンドウ位置を取得
		RECT lprc;//RECT:左上隅と右下隅の座標によって四角形を定義
		GetWindowRect(Direct3D::hwnd_, &lprc);

		//マウスカーソルの位置を取得
		POINT mouseCursorPosition{};//POINT:x 座標と y 座標を定義
		mouseCursorPosition.x = lprc.left + Direct3D::GetWindowCenterX();
		mouseCursorPosition.y = lprc.top + Direct3D::GetWindowCenterY();

		SetCursorPos(mouseCursorPosition.x,mouseCursorPosition.y);

		//マウスカーソルをセットする位置
		POINT setMoucePos{};

		//Xのウィンドウ中心
		setMoucePos.x = lprc.left + Direct3D::GetWindowCenterX();

		//Yのウィンドウ中心
		setMoucePos.y = lprc.top + Direct3D::GetWindowCenterY();

		//マウスカーソルの位置
		SetCursorPos(setMoucePos.x, setMoucePos.y);
	}
}

void Player::CameraMove()
{
	//マウスが動いた場合
	if (isMouseControl_)
	{
		//マウスとカメラの連動
		transform_.rotate_.y += Input::GetMouseMoveX() * MOUSE_CURSOR_HORIZONTAL_MOVE_SPEED;
		cameraHeight_ += Input::GetMouseMoveY() * MOUSE_CURSOR_VERTICAL_MOVE_SPEED;

		//カメラの位置設定
	    //カメラポジション
		XMFLOAT3 camPos = transform_.position_;

		//カメラ焦点位置
		XMVECTOR camTar = CAMERA_TARGET_POSITION;
		//プレイヤーの向く方向にカメラの焦点位置回転
		camTar = XMVector3TransformCoord(camTar, playerAngleYMatrix_);

		// XMFLOAT3型からXMVECTOR型に変換
		XMVECTOR VectorcamPos = XMLoadFloat3(&camPos);
		// XMVECTOR型同士の足し算
		XMVECTOR CameraPositionFocus = XMVectorAdd(VectorcamPos, camTar);
		XMFLOAT3 result{};
		// XMVECTOR型をXMFLOAT3型に変換
		XMStoreFloat3(&result, CameraPositionFocus);

		//カメラ位置と焦点を設定変更
		Camera::SetPosition(camPos);
		Camera::SetTarget(result);

		//SetTargetがXMFLOATなのでcamTarをXMFLOAT型にする
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





