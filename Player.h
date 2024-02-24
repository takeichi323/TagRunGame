#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//���������Ǘ�����N���X
class Player : public GameObject
{   
private:
    //Player�ړ����x
    const float PLAYERMOVE = 0.1;
    //1�t���[���̈ړ��x�N�g��
    const XMVECTOR vMove{ 0.0f,0.0f,0.1f,0.0f };//����(Z)+0.1

    Stage* pStage_;//���f���ԍ�

    //1�O�̃|�W�V����
    XMFLOAT3  prevPosition_;  

    int hModel_;    //���f���ԍ�
    int hSound_;    //�T�E���h�ԍ�
    //���x�����ɂ�����
    XMFLOAT3 fMove = XMFLOAT3(0, 0, 0);
    //�x�N�g������]�����鎞�g���s��
    XMMATRIX playerAngleYMatrix_;
    // XMVECTOR����XMFLOAT3�ւ̕ϊ��֐�
    XMFLOAT3 XMVectorToXMFLOAT3(const XMVECTOR& vector);


    //�J����(Player�̊�)�̍���
    float cameraHeight_;
    //�}�E�X���삪���ꂽ���ǂ���
    bool isMouseControl_;

    //�}�E�X����̏���
    void MouseControl();

    //�J�����̈ړ�����
    void CameraMove();

    //�v���C���[�����ʒu
    void PlayerInitialPosition();

    //�v���C���[�L�[�ړ�����
    //W:�O�i A:�� S:��� D:�E
    void PlayerKeyMove();
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

    
    

   
    
    //�ǂƂ̓����蔻��
    bool WallHitTest();
};
