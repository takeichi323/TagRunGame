#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class LifeGauge : public GameObject
{
private:
    int hPict_;    //�摜�ԍ�

public:
    //�R���X�g���N�^
    LifeGauge(GameObject* parent);

    //�f�X�g���N�^
    ~LifeGauge();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};

