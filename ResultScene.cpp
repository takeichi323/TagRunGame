#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
}
//初期化
void ResultScene::Initialize()
{
	hResult_= Image::Load("TagRunGame_v2.png");
	assert(hResult_ >= 0);
	// 画像の位置を変更する
    transformResultlog_.position_.x = -0.4f;
    transformResultlog_.position_.y = -0.5f;

	hBackTitle_ = Image::Load("EnterPUSH logo.png");
	assert(hBackTitle_ >= 0);
    transformTitelog_.position_.x = 0.8f;
    transformTitelog_.position_.y = -0.5f;
}

//更新
void ResultScene::Update()
{
    // 入力処理
    if (Input::IsKey(DIK_LEFT)) {
        if (selectedMode_ != 0) {
            selectedMode_ = 0; // ゲームシーンを選択
        }
    }
    
    if (Input::IsKey(DIK_RIGHT)) {
        if (selectedMode_ != 1) {
            selectedMode_ = 1; // タイトルを選択
        }
    }

    // スケール調整
    if (selectedMode_ == 0) {
        scaleNormal = 1.2f; // ふつうの画像を拡大
        scaleTitle = 1.0f;   // タイトル画像はそのまま
    }
    else {
        scaleNormal = 1.0f; // ふつうの画像はそのまま
        scaleTitle = 1.2f;   // タイトル画像を拡大
    }


    // 決定処理
    if (Input::IsKey(DIK_BACK)) {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        if (selectedMode_ == 0) {
            pSceneManager->ChangeScene(SCENE_ID_TEST); // ゲームシーンへ
        }
        else {
            pSceneManager->ChangeScene(SCENE_ID_TITLE); // タイトルシーンへ
        }
    }

		
}
//描画
void ResultScene::Draw()
{
    transformResultlog_.scale_ = XMFLOAT3(scaleNormal, scaleNormal, scaleNormal);
	Image::SetTransform(hResult_, transformResultlog_);
	Image::Draw(hResult_);

    // タイトル画像の描画
    transformTitelog_.scale_ = XMFLOAT3(scaleTitle, scaleTitle, scaleTitle);
	Image::SetTransform(hBackTitle_, transformTitelog_);
	Image::Draw(hBackTitle_);
}
//開放
void ResultScene::Release()
{
}


