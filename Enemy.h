#pragma once
#include "Engine/GameObject.h"

//���������Ǘ�����N���X
class Enemy : public GameObject
{
    int hModel_;    //���f���ԍ�
    

private:
    //�ʒu���3�����x�N�g���ɂ�����
    XMFLOAT3 GetObjectPosition(ID3D11DeviceContext* pContext, ID3D11Buffer* pObjectBuffer);


public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�v���C���[�̓����蔻���G�ɂ��ǉ�����
    //�����蔻�莩�̂��N���X��������������
};

