#include "Coin.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Coin::Coin(GameObject* parent)
    :GameObject(parent, "Coin"), hCoinModel_(-1)
{
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.2f);
	AddCollider(collision);
}

//�f�X�g���N�^
Coin::~Coin()
{
}

//������
void Coin::Initialize()
{
	//���f���f�[�^�̃��[�h
	hCoinModel_ = Model::Load("Coin.fbx");
	assert(hCoinModel_ >= 0);
	
}

//�X�V
void Coin::Update()
{
	CoinTrans.rotate_.y += 5.0f;
}

//�`��
void Coin::Draw()
{
	
	for (int x = 0; x < 34; x++)
	{
		for (int z = 0; z < 58; z++)
		{
			CoinTrans.position_.x = x + 0.5f;
			CoinTrans.position_.z = z + 0.5f;
			Model::SetTransform(hCoinModel_, CoinTrans);
			Model::Draw(hCoinModel_);
		}
	}
	
}

//�J��
void Coin::Release()
{
}

//�����ɓ�������
void Coin::OnCollision(GameObject* pTarget)
{
	

	//���������Ƃ��̏���
	if (pTarget->GetObjectName() == "Player")
	{
		KillMe();
		//pTarget->KillMe();

	}
}
