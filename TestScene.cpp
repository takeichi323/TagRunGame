#include "TestScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{

	Instantiate<Enemy>(this);
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
}

//更新
void TestScene::Update()
{
	
}

//描画
void TestScene::Draw()
{
}

//開放
void TestScene::Release()
{
}
