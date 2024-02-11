#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//初期化
void TitleScene::Initialize()
{
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
}

//開放
void TitleScene::Release()
{
}
