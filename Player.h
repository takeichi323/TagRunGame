#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Player : public GameObject
{   
    //Player�ړ����x
    const float PLAYERMOVE = 0.25;

    int hModel_;    //���f���ԍ�
    int hSound_;    //�T�E���h�ԍ�
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
