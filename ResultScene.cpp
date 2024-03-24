#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"


namespace {
	float startX;//�ړ��J�nX���W
	float endX;//�ړ��I��X���W
	float totalTime;//�ړ�����
	float currentTime;//���݂̎���
	int seq_line;//�����s���Ă���s
	float seq_time;//�V�[�P���X�����s���Ă��鎞��
	enum ACT {//��邱�Ƃ��R�}���h��
		A_SLIDEIN = 1,
		A_WAIT,
		A_SLIDEOUT,
		A_END
	};
	struct  Sequence {
		float time;//����
		ACT action;//��邱��
		float param;//�K�v�Ȓl
	};
	//����������Ă���
	Sequence tbl[] = {
		{0.0f,A_SLIDEIN,-5.0f},//�X���C�h�C��
		{3.0f,A_WAIT,0.0f},//�P�b�҂��Ă���
		{4.0f,A_SLIDEOUT,5.0f},//�X���C�h�A�E�g
		{5.0f,A_END,0.0f}//�����ŏ�����
	};
	ACT currentAction;
	bool canMove;
};

//�R���X�g���N�^
ResultScene::ResultScene(GameObject* parent)
	: GameObject(parent, "ResultScene")
{
	seq_line = -1;
	seq_time = 0.0f;
	canMove = false;
}
//������
void ResultScene::Initialize()
{
	hResult_= Image::Load("Result.png");
	assert(hResult_ >= 0);
	hBackTitle_ = Image::Load("EnterPUSH logo.png");
	assert(hBackTitle_ >= 0);
	transformResultlog_.position_.x = 0.0f;
	transformResultlog_.position_.y = 0.0f;

	startX = 5.0f;
	endX = 0;
	totalTime = 8.0f;
	currentTime = 0.0f;
	transform_.position_.x = startX;  // ����X���W��ݒ�
}
float easeInCubic(float x) {
	return x * x * x;
}
//�X�V
void ResultScene::Update()
{
	seq_time += 1.0f / 60.0f;//���Ԃ�i�߂�
	if (seq_time >= tbl[seq_line + 1].time) {//���̍s�����s����
		seq_line++;
		switch (tbl[seq_line].action) {
		case A_END:
			KillMe();
			break;
		case A_SLIDEIN:
			startX = tbl[seq_line].param;
			endX = 0;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;

			break;
		case A_WAIT:
			startX = transform_.position_.x;
			endX = transform_.position_.x;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			break;
		case A_SLIDEOUT:

			startX = transform_.position_.x;
			endX = tbl[seq_line].param;
			totalTime = tbl[seq_line + 1].time - seq_time;
			currentTime = 0.0f;
			

		}
		//���̍s�̎��s������

	}
	currentTime += 1.0f / 60.0f;//�P�t���[�����̎��Ԃ�i�܂���
	if (currentTime > totalTime)
		currentTime = totalTime;
	float t = currentTime / totalTime;//������0.0�`1.0�͈̔͂ɂ���
	float val = easeInCubic(t);
	transform_.position_.x = val * (endX - startX) + startX;

	
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
		Image::SetAlpha(hBackTitle_, currentTransparency);
		if (Input::IsKey(DIK_ESCAPE)) {
			SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_TITLE);
		}
}
//�`��
void ResultScene::Draw()
{
	
	Image::SetTransform(hResult_, transform_);
	Image::Draw(hResult_);

	Image::SetTransform(hBackTitle_, transformResultlog_);
	Image::Draw(hBackTitle_);
}
//�J��
void ResultScene::Release()
{
}

bool ResultScene::Finished()
{

	return seq_line >= sizeof(tbl) / sizeof(tbl[0]) - 1;
	return canMove;
	if (currentTime >= totalTime)
		return true;
	return false;
}
