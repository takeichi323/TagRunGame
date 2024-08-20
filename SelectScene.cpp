#include "SelectScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


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
    transformNormal_.position_.y = 0.0f;

    hPictHard_ = Image::Load("TagRunGame_v2.png");
    assert(hPictHard_ >= 0);
    // 画像の位置を変更する
    transformHard_.position_.x = 0.0f;
    transformHard_.position_.y = -0.2f;
}

//更新
void SelectScene::Update()
{
    // 入力処理
    if (Input::IsKey(DIK_UP)) {
        selectedMode_ = 0; // ふつうを選択
    }
    if (Input::IsKey(DIK_DOWN)) {
        selectedMode_ = 1; // むずかしいを選択
    }

    // 画像の切り替え
    if (!hPictNormal_) {
        hPictNormal_ = Image::Load("TagRunGame_v2.png");
    }
    if (!hPictHard_) {
        hPictHard_ = Image::Load("TagRunGame_v2.png");
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

    if (Input::IsKey(DIK_BACK))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
    }
    
}

//描画
void SelectScene::Draw()
{
    Image::SetTransform(hPictNormal_, transformNormal_);
    Image::Draw(hPictNormal_);
    Image::SetTransform(hPictHard_, transformHard_);
    Image::Draw(hPictHard_);
}

//開放
void SelectScene::Release()
{
}