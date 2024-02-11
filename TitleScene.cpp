#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"


//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene")
{
}

//������
void TitleScene::Initialize()
{
}

//�X�V
void TitleScene::Update()
{
    //�X�y�[�X�L�[��������Ă�����
    if (Input::IsKey(DIK_SPACE))
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_TEST);
    }
	
}

//�`��
void TitleScene::Draw()
{
}

//�J��
void TitleScene::Release()
{
}
