#include "Player.h"
#include"Stage.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"


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
    //カメラ位置
      //CameraPosition();
      //Direction();

	/*  HitTest();*/
    
    //スペースキーが押されていたら
    if (Input::IsKey(DIK_D))
    {
		// 移動前の位置を保存
		XMFLOAT3 originalPosition = transform_.position_;
        transform_.position_.x += PLAYERMOVE;
       // Audio::Play(hSound_);
		// 壁との当たり判定
		if (WallHitTest())
		{
			// 当たった場合は元の位置に戻す
			transform_.position_ = originalPosition;
		}
	
		
    }
    //スペースキーが押されていたら
    if (Input::IsKey(DIK_A))
    {
		// 移動前の位置を保存
		XMFLOAT3 originalPosition = transform_.position_;
        transform_.position_.x -= PLAYERMOVE;
       // Audio::Stop(hSound_);
		if (WallHitTest())
		{
			// 当たった場合は元の位置に戻す
			transform_.position_ = originalPosition;
		}
    }
    if (Input::IsKey(DIK_W))
    {
		// 移動前の位置を保存
		XMFLOAT3 originalPosition = transform_.position_;
        transform_.position_.z += PLAYERMOVE;
		if (WallHitTest())
		{
			// 当たった場合は元の位置に戻す
			transform_.position_ = originalPosition;
		}
       
    }
    if (Input::IsKey(DIK_S))
    {
		// 移動前の位置を保存
		XMFLOAT3 originalPosition = transform_.position_;
        transform_.position_.z -= PLAYERMOVE;
		if (WallHitTest())
		{
			// 当たった場合は元の位置に戻す
			transform_.position_ = originalPosition;
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

//カメラ位置(一人称)
void Player::CameraPosition()
{
    //1フレームの移動ベクトル
   // XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//奥に0.1ｍ
    //オブジェクトの現在地をベクトル型に変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    Camera::SetPosition(transform_.position_);
    XMFLOAT3 camTarget;
    XMStoreFloat3(&camTarget, vPos + vMove);
    Camera::SetTarget(camTarget);
}

bool Player::WallHitTest()
{
	// PlayerクラスからStageクラスへの参照を取得
	Stage* stage = dynamic_cast<Stage*>(GetParent()->FindChildObject("Stage"));
	//もし取得できた場合
	if (stage)
	{
		// Playerの位置をステージ座標系に変換→キャストってやーつ
		int playerX = static_cast<int>(transform_.position_.x);
		int playerZ = static_cast<int>(transform_.position_.z);
		// ステージ上の座標が壁かどうかをチェック
		if (stage->IsWall(playerX, playerZ))
		{
			// 壁と当たっている場合はtrueを返す
			return true;
		}
	}
	//当たっていない場合falseを返す
	return false;
	
}





