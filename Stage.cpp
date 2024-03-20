#include "Stage.h"
#include "Engine/Model.h"
#include "TestScene.h"
#include "Engine/CsvReader.h"
#include "Coin.h"


//コンストラクタ
Stage::Stage(GameObject* parent)
	: GameObject(parent, "Stage"), hModel_{ -1,-1 }, table_(nullptr)
{

	CsvReader csv;
	csv.Load("map.csv");

	int width_ = csv.GetWidth();
	int height_ = csv.GetHeight();

	//table_ = new int* [csv.GetWidth()];
	table_ = new int* [width_];

	for (int x = 0; x < width_; x++)
	{
		table_[x] = new int[height_];
		for (int z = 0; z < height_; z++)
		{
			table_[x][z] = csv.GetValue(x, z); // マップデータを取得し、table_ に格納
	

		}
	}
}

//初期化
void Stage::Initialize()
{
	
	const char* fileName[] = { "floar.fbx", "floarbox.fbx"};

	//コインのモデルデータを読み込み
	hCoinModel_ = Model::Load("Coin.fbx");
	assert(hCoinModel_ >= 0);

	//CSVデータを読み込み、コインの位置を特定
	CsvReader coinCsv;
	coinCsv.Load("coin_map.csv");

	//コインを配置する座標のリスト
	std::vector<std::pair<int, int>>coinPosition;

	//CSVデータを読み込んで、コインが配置されている座標を取得
	for (int x = 0; x < coinCsv.GetWidth(); x++) {
		for (int z = 0; z < coinCsv.GetHeight(); z++) {
			if (coinCsv.GetValue(x, z) == 1) {
				coinPosition.push_back(std::make_pair(x, z));
			}
		}
	}
	

	////コインを配置
	//for (const auto& position : coinPosition) {
	//	Coin coin;
	//	coin.CoinTrans.position_.x = position.first + 0.5f;
	//	coin.CoinTrans.position_.z = position.second + 0.5f;
	//	coins.push_back(coin); // coins ベクターにコインを追加
	//}


	//モデルデータのロード
	for (int i = 0; i < TYPE_MAX; i++)
	{
		hModel_[i] = Model::Load(fileName[i]);
		assert(hModel_[i] >= 0);
	}

	
}

//更新
void Stage::Update()
{
	CoinTrans.rotate_.y += 5.0f;
}

//描画
void Stage::Draw()
{

	Transform blockTrans;

	for (int x = 0; x < 36; x++)
	{
		for (int z = 0; z < 60; z++)
		{
			
				CoinTrans.position_.x = x + 0.5f;
				CoinTrans.position_.z = z + 0.5f;
				Model::SetTransform(hCoinModel_, CoinTrans);
				Model::Draw(hCoinModel_);
				SphereCollider* collision = new SphereCollider(CoinTrans.position_, 0.2f);
			     AddCollider(collision);
			
			blockTrans.position_.x = x + 1;
			blockTrans.position_.z = z;

			int type = table_[x][z];
			Model::SetTransform(hModel_[type], blockTrans);
			Model::Draw(hModel_[type]);


		}
	}
		
}


/*コイン(仮)マップ上に配置
マップの床になっている所に配置
"floar.fbx"＝0になっている場所
当たり判定を付ける
コインを取ったら音鳴らす
Y軸で常に回転させる*/

//開放
void Stage::Release()
{
	for (int x = 0; x < width_; x++)
	{
		delete[] table_[x];
	}
	delete[] table_;
}

bool Stage::IsWall(int x, int z)
{
	if (table_[x][z] == TYPE_WALL)
		return true;
	else
		return false;

	
}
