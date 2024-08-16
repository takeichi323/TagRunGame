#include "TitleScene.h"
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1), hTitlelog_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
    
	//画像データのロード
    //Press Any Buttonの画像
	hPict_ = Image::Load("EnterPUSH logo.png");
	assert(hPict_ >= 0);
	// 画像の位置を変更する
    transform_.position_.x = 0.0f;
    transform_.position_.y =- 0.6f;

    
    hTitlelog_ = Image::Load("TagRunGame_v2.png");
    assert(hTitlelog_ >= 0);
    // 画像の位置を変更する
    transformTitlelog_.position_.x = 0.0f;
    transformTitlelog_.position_.y = 0.0f;
}

//更新
void TitleScene::Update()
{
	/*if (Input::IsKey(DIK_RETURN)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}*/
    
    if (!transitionmove_ && Input::IsKey(DIK_RETURN)) {
        transitionmove_ = true;
        currentTransparency_ = 0;
    }

    if (transitionmove_) {
        // 点滅効果
        if (increasing_) {
            currentTransparency_ += 10; // 点滅の速度を変更したい場合はこの値を調整
            if (currentTransparency_ >= transparencyMax_) {
                currentTransparency_ = transparencyMax_;
                increasing_ = false;
            }
        }
        else {
            currentTransparency_ -= 10;
            if (currentTransparency_ <= 0) {
                currentTransparency_ = 0;
                increasing_ = true;
                // 画面暗転を開始
                transitionTransparency_ += 5;
                if (transitionTransparency_ >= transparencyMax_) {
                    transitionTransparency_ = transparencyMax_;
                    // シーン切り替え
                    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
                    pSceneManager->ChangeScene(SCENE_ID_TEST);
                }
            }
        }
    }
    else {
        // 通常時の透明度アニメーション
        if (increasing_) {
            currentTransparency_ += 5;
            if (currentTransparency_ >= transparencyMax_) {
                increasing_ = false;
            }
        }
        else {
            currentTransparency_ -= 5;
            if (currentTransparency_ <= 0) {
                increasing_ = true;
            }
        }
    }

    // 画像の透明度を設定
    Image::SetAlpha(hPict_, currentTransparency);


}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

    Image::SetTransform(hTitlelog_, transformTitlelog_);
    Image::Draw(hTitlelog_);
}

//開放
void TitleScene::Release()
{
}