#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Coin : public GameObject
{

    int hCoinModel_;       //�R�C�����f��
   
public:
    //�R���X�g���N�^
    Coin(GameObject* parent);
    Coin() {}

    

    //�f�X�g���N�^
    ~Coin();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;
    Transform CoinTrans;
    //std::vector<Coin> coins; // coins �����o�[�̒�`


};

/*�R�C���̒P�̉�
�@*/
