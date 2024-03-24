#include "Player.h"
#include "Engine/Model.h"

#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"
#include "Engine/SphereCollider.h"


//コンストラクタ
Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1),  pStage_(nullptr)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
	//当たり判定のサイズ
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.21f, 0.0f), 0.4f);
	AddCollider(collision);

	//モデルデータのロード
	hModel_ = Model::Load("Pacplayer.fbx");
	assert(hModel_ >= 0);

	////サウンドデータのロード
	//hSound_ = Audio::Load("Jazz 1.wav");
	//assert(hSound_ >= 0);

	//仮ポジション
	//transform_.position_.y += 0.5;
	transform_.position_ = XMFLOAT3(2.0, 0.1, 2.5);
	//transform_.position_ = XMFLOAT3(10.5, 5.0, 1.5);
   
	//全体のマップを確認するためのカメラ位置
	Camera::SetPosition(XMFLOAT3(25, 50, -8));
	Camera::SetTarget(XMFLOAT3(25, 10, 10));

	pStage_ = (Stage*)FindObject("Stage");


}


//更新
void Player::Update()
{
	
	//カメラ位置
	CameraPosition();
	PlayerMove();

	
	

	//壁との判定
	int checkX1, checkX2;
	int checkZ1, checkZ2;

	//右
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

	//左
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

	//奥
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

	//手前
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

// XMVECTORからXMFLOAT3への変換関数
XMFLOAT3 XMVectorToXMFLOAT3(const XMVECTOR& vector)
{
	XMFLOAT3 result;
	XMStoreFloat3(&result, vector);
	return result;
}

//カメラ位置(一人称)
void Player::CameraPosition()
{

	//1フレームの移動ベクトル
	XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//奥に0.1ｍ
	// transform_.rotate_.y度回転させる行列を作成
	XMMATRIX mRotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	//カメラの相対位置
	XMVECTOR vCamRelative = { 0,5,-10,0 };
	//カメラの相対位置をプレイヤーの回転行列で変換
	vCamRelative = XMVector3Transform(vCamRelative, mRotY);
	//カメラの最終的な位置を計算
	XMVECTOR vCamPos = vPos + vCamRelative;

	// XMVECTORからXMFLOAT3へ変換
	XMFLOAT3 camPos;
	camPos = XMVectorToXMFLOAT3(vCamPos);


	//カメラの位置を設定
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



	////オブジェクトの現在地をベクトル型に変換
	//XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
	//Camera::SetPosition(transform_.position_);
	//XMFLOAT3 camTarget;
	//XMStoreFloat3(&camTarget, vPos + vMove);
	//Camera::SetTarget(camTarget);
}

//プレイヤーの移動
void Player::PlayerMove()
{
	/*カメラの方向に合わせて移動する
	・プレイヤーの向いてる方向を取得
	・プレイヤの移動関数内でカメラの向いている方向でプレイヤーを移動させる*/

	prevPosition_ = transform_.position_;
	XMFLOAT3 move{ 0,0,0 };
	// カメラの向きを取得
	XMFLOAT3 forward = Camera::GetForwardVector();


	//右移動
	if (Input::IsKey(DIK_D))
	{
		move.x += PLAYERMOVE * forward.z;
		move.z -= PLAYERMOVE * forward.x;
		// Audio::Play(hSound_);
	}
	//左移動
	if (Input::IsKey(DIK_A))
	{
		
		move.x -= PLAYERMOVE * forward.z;
		move.z += PLAYERMOVE * forward.x;
		// Audio::Stop(hSound_);
	}
	//前移動
	if (Input::IsKey(DIK_W))
	{
		move.x += PLAYERMOVE * forward.x;
		move.z += PLAYERMOVE * forward.z;


	}
	//後移動
	if (Input::IsKey(DIK_S))
	{
		move.x -= PLAYERMOVE * forward.x;
		move.z -= PLAYERMOVE * forward.z;

		

	}

	//ダッシュボタン:左シフト
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

	//transform_.position_ = transform_.position_ + move;
    // 移動を適用
	transform_.position_.x += move.x;
	transform_.position_.z += move.z;
}







