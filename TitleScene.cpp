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
    transformpushlog_.position_.x = PUSHLOGPOS_X;
    transformpushlog_.position_.y = PUSHLOGPOS_Y;

    
    hTitlelog_ = Image::Load("TagRunGame_v2.png");
    assert(hTitlelog_ >= 0);
    // 画像の位置を変更する
    transformTitlelog_.position_.x = TITLELOGPOS_X;
    transformTitlelog_.position_.y = TITLELOGPOS_Y;

    hBlack_ = Image::Load("black.png"); // 黒い四角形画像のロード
    assert(hBlack_ >= 0);
    
}

//更新
void TitleScene::Update()
{
    
    if (!transitionmove_ && Input::IsKey(DIK_RETURN)) {
        transitionmove_ = true;
        currentTransparency_ = 0;
    }

    if (transitionmove_) {
        // 点滅効果
        if (increasing_) {
            currentTransparency_ += BLINKING_SPEED; // 点滅の速度を変更したい場合はこの値を調整
            if (currentTransparency_ >= transparencyMax_) {
                currentTransparency_ = transparencyMax_;
                increasing_ = false;
            }
        }
        else {
            currentTransparency_ -= BLINKING_SPEED;
            if (currentTransparency_ <= 0) {
                currentTransparency_ = 0;
                increasing_ = true;
                // 画面暗転を開始
                transitionTransparency_ += fadeSpeed_;
                if (transitionTransparency_ >= transparencyMax_) {
                    transitionTransparency_ = transparencyMax_;
                    // シーン切り替え
                    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
                    pSceneManager->ChangeScene(SCENE_ID_SELECT);
                }
            }
        }
    }
    else {
        // 通常時の透明度アニメーション
        if (increasing_) {
            currentTransparency_ += TRANSPARENCY_UPDATE;//透明度を更新
            if (currentTransparency_ >= transparencyMax_) {
                increasing_ = false;
            }
        }
        else {
            currentTransparency_ -= TRANSPARENCY_UPDATE;//透明度を更新
            if (currentTransparency_ <= 0) {
                increasing_ = true;
            }
        }
    }

    // 画像の透明度を設定
    Image::SetAlpha(hPict_, currentTransparency_);


}

//描画
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transformpushlog_);
	Image::Draw(hPict_);

    Image::SetTransform(hTitlelog_, transformTitlelog_);
    Image::Draw(hTitlelog_);

    if (transitionmove_) {
        Image::SetAlpha(hBlack_, transitionTransparency_);
        Image::SetTransform(hBlack_, transformBlack_);
        Image::Draw(hBlack_);
    }
}

//開放
void TitleScene::Release()
{
}