#include "TitleScene.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Engine/Image.h"


//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hSubLogo_(-1)
{
}

//������
void TitleScene::Initialize()
{
    start_ = Instantiate<Button>(this);
    start_->SetImage("StartTest");
    start_->SetPosition(600, 650);//�E�B���h�E�̉���1280,�c720
    start_->SetNextScene(SELECT);
    start_->SetIsFlash(false);

    //�摜���[�h
    hSubLogo_ = Image::Load("EnterPUSH logo.png");
    assert(hSubLogo_ >= 0);
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
    Image::SetTransform(hSubLogo_, transform_);
    Image::Draw(hSubLogo_);
}

//�J��
void TitleScene::Release()
{
}
