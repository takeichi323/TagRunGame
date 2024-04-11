#include "Coin.h"
#include "Engine/Model.h"

//コンストラクタ
Coin::Coin(GameObject* parent)
    :GameObject(parent, "Coin"), hCoinModel_(-1)
{
	
}

//デストラクタ
Coin::~Coin()
{
}

//初期化
void Coin::Initialize()
{
	
	
}

//更新
void Coin::Update()
{
	CoinTrans.rotate_.y += 5.0f;
}

//描画
void Coin::Draw()
{
	
}

//開放
void Coin::Release()
{
}

//何かに当たった
void Coin::OnCollision(GameObject* pTarget)
{
	

	//当たったときの処理
	if (pTarget->GetObjectName() == "Player")
	{
		KillMe();
		pTarget->KillMe();

	}
}
