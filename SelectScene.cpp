#include "SelectScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


//コンストラクタ
SelectScene::SelectScene(GameObject* parent)
    :GameObject(parent, "SelectScene"), hTitlelog_(-1)
{
}

//デストラクタ
SelectScene::~SelectScene()
{
}

//初期化
void SelectScene::Initialize()
{
    hTitlelog_ = Image::Load("TagRunGame_v2.png");
    assert(hTitlelog_ >= 0);
    // 画像の位置を変更する
    transformTitlelog_.position_.x = 0.0f;
    transformTitlelog_.position_.y = 0.0f;
}

//更新
void SelectScene::Update()
{
    if (Input::IsKey(DIK_BACK))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
    }
    
}

//描画
void SelectScene::Draw()
{
    Image::SetTransform(hTitlelog_, transformTitlelog_);
    Image::Draw(hTitlelog_);
}

//開放
void SelectScene::Release()
{
}