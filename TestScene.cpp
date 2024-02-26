#include "TestScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Coin.h"
#include "LifeGauge.h"


//コンストラクタ
TestScene::TestScene(GameObject * parent)
	: GameObject(parent, "TestScene")
{
}

//初期化
void TestScene::Initialize()
{
	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
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
