#include "TitleScene.h"
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//初期化
void TitleScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("EnterPUSH logo.png");
	assert(hPict_ >= 0);

	// 画像の位置を変更する
	transform_.position_.x = 0.0f; 
	transform_.position_.y =- 0.6f; 
}

//更新
void TitleScene::Update()
{
	if (Input::IsKey(DIK_RETURN)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
	
    // 透明度の変化を制御するフラグ
    static bool increasing = true;
    // 透明度の増減速度
    static int transparencyStep = 5;
    // 最大透明度
    static int transparencyMax = 255;
    // 現在の透明度
    static int currentTransparency = 0;
    // 透明度の増減処理
    if (increasing) {
        currentTransparency += transparencyStep;
        if (currentTransparency >= transparencyMax) {
            increasing = false;
        }
    }
    else {
        currentTransparency -= transparencyStep;
        if (currentTransparency <= 0) {
            increasing = true;
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
}

//開放
void TitleScene::Release()
{
}