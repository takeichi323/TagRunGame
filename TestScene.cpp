#include "TestScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//������
void TestScene::Initialize()
{

	Instantiate<Enemy>(this);
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
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
