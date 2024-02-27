#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

#include "Engine/Image.h"


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hSubLogo_(-1)
{
}

//初期化
void TitleScene::Initialize()
{

    //画像ロード
    hSubLogo_ = Image::Load("EnterPUSH logo.png");
    assert(hSubLogo_ >= 0);
}

//更新
void TitleScene::Update()
{
    //スペースキーが押されていたら
    if (Input::IsKey(DIK_SPACE))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
    }
	
}

//描画
void TitleScene::Draw()
{
    Image::SetTransform(hSubLogo_, transform_);
    Image::Draw(hSubLogo_);
}

//開放
void TitleScene::Release()
{
}
