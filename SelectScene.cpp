#include "SelectScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"


//コンストラクタ
SelectScene::SelectScene(GameObject* parent)
    :GameObject(parent, "SelectScene")
{
}

//デストラクタ
SelectScene::~SelectScene()
{
}

//初期化
void SelectScene::Initialize()
{
}

//更新
void SelectScene::Update()
{
    if (Input::IsKey(DIK_RETURN))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
    }
    
}

//描画
void SelectScene::Draw()
{
}

//開放
void SelectScene::Release()
{
}