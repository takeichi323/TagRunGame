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
	//コインモデルのロード
	hCoinModel_ = Model::Load("Coin.fbx");
	assert(hCoinModel_ >= 0);
	/*コインをロード
	　描画させる
	 　　　↑
　この処理をステージでCSVの値が２の場合に表示させる*/
	
}

//更新
void Coin::Update()
{
	CoinTrans.rotate_.y += 5.0f;
}

//描画
void Coin::Draw()
{
	/*Model::SetTransform(hCoinModel_, transform_);
	Model::Draw(hCoinModel_);*/
	
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
