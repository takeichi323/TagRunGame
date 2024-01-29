#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/Debug.h"


//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1), hSound_(-1), pStage_(nullptr)
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
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
    AddCollider(collision);

    //モデルデータのロード
    hModel_ = Model::Load("Pacplayer.fbx");
    assert(hModel_ >= 0);

    //サウンドデータのロード
    hSound_ = Audio::Load("Jazz 1.wav");
    assert(hSound_ >= 0);

    //仮ポジション
    //transform_.position_.y += 0.5;
    transform_.position_ = XMFLOAT3(1.0, 0.5, 1.5);
   
    //全体のマップを確認するためのカメラ位置
    Camera::SetPosition(XMFLOAT3(25, 50, -8));
    Camera::SetTarget(XMFLOAT3(25, 10, 10));

    pStage_ = (Stage*)FindObject("Stage");


}

//更新
void Player::Update()
{
    prevPosition_ = transform_.position_;
    //カメラ位置
      //CameraPosition();
    
   //右移動
    if (Input::IsKey(DIK_D))
    {
        transform_.position_.x += PLAYERMOVE;
       // Audio::Play(hSound_);
    }
   //左移動
    if (Input::IsKey(DIK_A))
    {
        transform_.position_.x -= PLAYERMOVE;
       // Audio::Stop(hSound_);
    }
    //前移動
    if (Input::IsKey(DIK_W))
    {
        transform_.position_.z += PLAYERMOVE;
       
    }
    //後移動
    if (Input::IsKey(DIK_S))
    {
        transform_.position_.z -= PLAYERMOVE;

    }

    
    //壁との判定
    int checkX1, checkX2;
    int checkZ1, checkZ2;

    //右
    {
        checkX1 = (int)(transform_.position_.x + 0.3f);
        checkZ1 = (int)(transform_.position_.z + 0.2f);

        checkX2 = (int)(transform_.position_.x + 0.3f);
        checkZ2 = (int)(transform_.position_.z - 0.2f);

        if (pStage_->IsWall(checkX1, checkZ1) == true ||
            pStage_->IsWall(checkX2, checkZ2) == true)
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

//カメラ位置(一人称)
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





