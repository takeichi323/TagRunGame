#include "SelectScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/Audio.h"


//コンストラクタ
SelectScene::SelectScene(GameObject* parent)
    :GameObject(parent, "SelectScene"), hPictNormal_(-1)
{
}

//デストラクタ
SelectScene::~SelectScene()
{
}

//初期化
void SelectScene::Initialize()
{
    hPictNormal_ = Image::Load("TagRunGame_v2.png");
    assert(hPictNormal_ >= 0);
    // 画像の位置を変更する
    transformNormal_.position_.x = 0.0f;
    transformNormal_.position_.y = 0.3f;

    hPictHard_ = Image::Load("TagRunGame_v2.png");
    assert(hPictHard_ >= 0);
    // 画像の位置を変更する
    transformHard_.position_.x = 0.0f;
    transformHard_.position_.y = -0.3f;

    //サウンドデータのロード
    soundSelect_ = Audio::Load("select.wav");
    assert(soundSelect_ >= 0); 
}

//更新
void SelectScene::Update()
{
    // 入力処理
    if (Input::IsKey(DIK_UP)) {
        if (!keyUpPressed && selectedMode_ != 0) {
            selectedMode_ = 0; // ふつうを選択
            Audio::Stop(soundSelect_); // 再生中の効果音を強制的に停止
            Audio::Play(soundSelect_); // 効果音を再生
            keyUpPressed = true; // 上キーが押されている状態に設定
        }
    }
    else {
        keyUpPressed = false; // 上キーが離されたらリセット
    }

    if (Input::IsKey(DIK_DOWN)) {
        if (!keyDownPressed && selectedMode_ != 1) {
            selectedMode_ = 1; // むずかしいを選択
            Audio::Stop(soundSelect_); // 再生中の効果音を強制的に停止
            Audio::Play(soundSelect_); // 効果音を再生
            keyDownPressed = true; // 下キーが押されている状態に設定
        }
    }
    else {
        keyDownPressed = false; // 下キーが離されたらリセット
    }

    //// 画像の切り替え
    //if (!hPictNormal_) {
    //    hPictNormal_ = Image::Load("TagRunGame_v2.png");
    //}
    //if (!hPictHard_) {
    //    hPictHard_ = Image::Load("TagRunGame_v2.png");
    //}
    // 
    // スケール調整
    if (selectedMode_ == 0) {
        scaleNormal = 1.2f; // ふつうの画像を拡大
        scaleHard = 1.0f;   // むずかしいの画像はそのまま
    }
    else {
        scaleNormal = 1.0f; // ふつうの画像はそのまま
        scaleHard = 1.2f;   // むずかしいの画像を拡大
    }


    // 決定処理
    if (Input::IsKey(DIK_BACK)) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        if (selectedMode_ == 0) {
            pSceneManager->ChangeScene(SCENE_ID_TEST); // ふつうのゲームモードへ(ゲームシーン)
        }
        else {
            pSceneManager->ChangeScene(SCENE_ID_TITLE); // むずかしいゲームモードへ（タイトルシーン）
        }
    }

    /*if (Input::IsKey(DIK_BACK))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
    }*/
    
}

//描画
void SelectScene::Draw()
{
    // ふつうの画像の描画
    transformNormal_.scale_ = XMFLOAT3(scaleNormal, scaleNormal, scaleNormal);
    Image::SetTransform(hPictNormal_, transformNormal_);
    Image::Draw(hPictNormal_);

    // むずかしいの画像の描画
    transformHard_.scale_ = XMFLOAT3(scaleHard, scaleHard, scaleHard);
    Image::SetTransform(hPictHard_, transformHard_);
    Image::Draw(hPictHard_);
}

//開放
void SelectScene::Release()
{
}