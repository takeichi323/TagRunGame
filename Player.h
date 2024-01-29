#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"




//���������Ǘ�����N���X
class Player : public GameObject
{   
    //Player�ړ����x
    const float PLAYERMOVE = 0.05;

    int hModel_;    //���f���ԍ�
    int hSound_;    //�T�E���h�ԍ�

    XMFLOAT3  prevPosition_;   //prev(previous)�O
    Stage* pStage_;//���f���ԍ�

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();
    //������
    void Initialize() override;
    //�X�V
    void Update() override;
    //�`��
    void Draw() override;
    //�J��
    void Release() override;
    //�v���C���[�̃J�����ʒu
    void CameraPosition();

    
    
};
