#pragma once
#include "Engine/GameObject.h"


enum
{
	TYPE_FLOOR,
	TYPE_WALL,
	TYPE_MAX
};


//�����V�[�����Ǘ�����N���X
class Stage : public GameObject
{

	int hModel_[TYPE_MAX];    //���f���ԍ�
	int hCoinModel_;
	
	int** table_;
	int width_, height_;

	Transform CoinTrans;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Stage(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	//�w�肵���ʒu���ʂ�邩�ʂ�Ȃ����𒲂ׂ�
	//����:x,z�@���ׂ�ʒu
	//�߂�l:�@�ʂ�Ȃ���true/�ʂ�Ȃ�=false
	bool IsWall(int x, int z);
};
