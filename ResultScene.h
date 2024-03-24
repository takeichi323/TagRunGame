#pragma once
#include "Engine/GameObject.h"


class ResultScene : public GameObject
{
private:
	int hResult_;
	int hBackTitle_;
	Transform transformResultlog_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultScene(GameObject* parent);
	//������
	void Initialize() override;
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;

	//�J��
	void Release() override;
	bool Finished();
};
