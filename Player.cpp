#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Audio.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"



#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid.lib")
#pragma comment(lib, "mfreadwrite.lib")









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


    /// <summary>
    /// ///////////////////////////////////////////
    /// </summary>
    HRESULT hr = MFStartup(MF_VERSION);
    if (FAILED(hr)) {
        // 初期化に失敗
        // エラー処理
    }
    IMFSourceReader* pReader = nullptr;

    hr = MFCreateSourceReaderFromURL(L"TouhokuDenshi_splash.avi", nullptr, &pReader);
    if (FAILED(hr)) {
        // Source Reader の作成に失敗
        // エラー処理
    }
    IMFMediaType* pMediaType = nullptr;

    hr = MFCreateMediaType(&pMediaType);
    if (SUCCEEDED(hr)) {
        hr = pMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Video);
    }

    hr = pReader->SetCurrentMediaType(MF_SOURCE_READER_FIRST_VIDEO_STREAM, nullptr, pMediaType);
    while (true) {
        DWORD dwFlags = 0;
        LONGLONG llTimeStamp = 0;
        IMFSample* pSample = nullptr;

        hr = pReader->ReadSample(MF_SOURCE_READER_FIRST_VIDEO_STREAM, 0, nullptr, &dwFlags, &llTimeStamp, &pSample);
        if (FAILED(hr)) {
            // サンプルの読み取りに失敗または終了
            break;
        }

        if (dwFlags & MF_SOURCE_READERF_ENDOFSTREAM) {
            // ファイルの終端に到達
            break;
        }

        // テクスチャにフレームを描画する処理
    }
    pReader->Release();
    pMediaType->Release();
    MFShutdown();
    /////////////////////////////////////////////////////////////////

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


