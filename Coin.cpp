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
	//モデルデータのロード
	hCoinModel_ = Model::Load("Coin.fbx");
	assert(hCoinModel_ >= 0);
	
}

//更新
void Coin::Update()
{
	CoinTrans.rotate_.y += 5.0f;
}

//描画
void Coin::Draw()
{
	
	for (int x = 0; x < 34; x++)
	{
		for (int z = 0; z < 58; z++)
		{
			CoinTrans.position_.x = x+0.5f ;
			CoinTrans.position_.z = z+0.5f;
			Model::SetTransform(hCoinModel_, CoinTrans);
			Model::Draw(hCoinModel_);
		}
	}
	
}

//開放
void Coin::Release()
{
}