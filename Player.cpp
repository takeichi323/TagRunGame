#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"




//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), hSound_(-1)
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
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //サウンドデータのロード
    hSound_ = Audio::Load("Jazz 1.wav");
    assert(hSound_ >= 0);
}

//更新
void Player::Update()
{
    //カメラ位置
      CameraPosition();
    
    //スペースキーが押されていたら
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += 0.25;
        Audio::Play(hSound_);
    }
    //スペースキーが押されていたら
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= 0.25;
        Audio::Stop(hSound_);
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

void Player::CameraPosition()
{
    //1フレームの移動ベクトル
    XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//奥に0.1ｍ
    //オブジェクトの現在地をベクトル型に変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    Camera::SetPosition(transform_.position_);
    XMFLOAT3 camTarget;
    XMStoreFloat3(&camTarget, vPos + vMove);
    Camera::SetTarget(camTarget);
}


