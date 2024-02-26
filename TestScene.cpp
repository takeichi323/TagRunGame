#include "TestScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Coin.h"
#include "LifeGauge.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{

	Instantiate<Enemy>(this);
	Instantiate<Coin>(this);
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Instantiate<LifeGauge>(this);
	
}

//�X�V
void TestScene::Update()
{
}

//�`��
void TestScene::Draw()
{
}

//�J��
void TestScene::Release()
{
}
