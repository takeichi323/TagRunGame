#include "TitleScene.h"
#include "Engine/Input.h"
#include "Stage.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

//�R���X�g���N�^
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"), hPict_(-1)
{
}

//������
void TitleScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("EnterPUSH logo.png");
	assert(hPict_ >= 0);

	// �摜�̈ʒu��ύX����
	transform_.position_.x = 0.0f; 
	transform_.position_.y =- 0.6f; 
}

//�X�V
void TitleScene::Update()
{
	if (Input::IsKey(DIK_RETURN)) {
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_TEST);
	}
	
    // �����x�̕ω��𐧌䂷��t���O
    static bool increasing = true;
    // �����x�̑������x
    static int transparencyStep = 5;
    // �ő哧���x
    static int transparencyMax = 255;
    // ���݂̓����x
    static int currentTransparency = 0;
    // �����x�̑�������
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

    // �摜�̓����x��ݒ�
    Image::SetAlpha(hPict_, currentTransparency);


}

//�`��
void TitleScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void TitleScene::Release()
{
}